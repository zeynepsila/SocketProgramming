#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>  //Linux için
#include <arpa/inet.h>   //Linux için
//#include <Winsock2.h>  //windows için
//#include <winsock.h>   //windows için

int main(void)
{
    //TCP SOCKETİ OLUŞTURMA ISLEMI
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); //AP_INET = IPv4, SOCK_STREAM = TCP

    if(socket_desc < 0){
        printf("Hata : Socket olusturulamadi!\n");
        return EXIT_FAILURE;
    }

    printf("Socket basariyla olusturuldu!\n");

    //SERVER ADRESINI OLUSTURMA ISLEMI
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //SUNUCUYA BAGLANMA ISLEMI
    int connect_result = connect(socket_desc, (struct sockaddr*) &server_addr, sizeof(server_addr));

    if(connect_result < 0){
        printf("HATA: BAGLANTI KURULAMADI!\n");
        return EXIT_FAILURE;
    }
    printf("BAGLANTI BASARIYLA KURULDU!\n");

    // HEDEF ADRES: 127.0.0.1:3000 şeklinde ifade edilir. 127.0.0.1 ip adresinin 3000 numaralı portu anlamına gelir
    
    //MESAJI OLUSTURMA
    char client_message[1024];
    printf("Iletmek istediginiz mesaji giriniz: ");
    fgets(client_message, 1024, stdin);
    strtok(client_message, "\n");

    //MESAJI SUNUCUYA GONDERME ISLEMI
    int send_result = send(socket_desc, client_message, strlen(client_message), 0);

    if(send_result <0 ){
        printf("HATA: MESAJ GONDERME ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }

    printf("MESAJ GONDERME ISLEMI BASARILI!\n");

    //SUNUCUDAN GELECEK MESAJ ICIN HAFIZADAN YER AYIRMA ISLEMI
    char server_message[1024];
    memset(server_message, '\0', strlen(server_message));

    //SUNUCUDAN MESAJI AL
    int receive_result;
    receive_result = recv(socket_desc, server_message, sizeof(server_message), 0);

    if(receive_result < 0){
        printf("HATA: MESAJ ALMA ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }

    printf("MESAJ ALMA ISLEMI BASARILI! Mesaj: %s", server_message);

    return EXIT_SUCCESS;
}
