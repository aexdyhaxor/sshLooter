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

```bash
# Gunakan dnf atau yum
sudo dnf install gcc libcurl-devel pam-devel git make
