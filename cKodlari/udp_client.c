#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>  //Linux için
#include <arpa/inet.h>   //Linux için
//#include <Winsock2.h>  //windows için
//#include <winsock.h>   //windows için

int main(void){

    //UDP SOCKETİ OLUŞTURMA ISLEMI
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //IPPROTO_UDP: UDP PROTOKOLU

    if(socket_desc < 0){
        printf("Hata : Socket olusturulamadi!\n");
        return EXIT_FAILURE;
    }

    printf("Socket basariyla olusturuldu!\n");

    //SERVER ADRESINI OLUSTURMA ISLEMI
    
    struct sockaddr_in server_addr;
    socklen_t server_socklen = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //MESAJI OLUSTURMA ISLEMI
    char client_message[1024];
    printf("Iletmek istediginiz mesaji giriniz: ");
    fgets(client_message, 1024, stdin);
    strtok(client_message, "\n");

    //OLUSTURULAN MESAJI SUNUCUYA GONDERME ISLEMI
    int send_result;
    send_result = sendto(socket_desc, client_message, strlen(client_message), 0, (struct sockaddr*) &server_addr, sizeof(server_addr));

    if(send_result < 0){
        printf("HATA: MESAJ GONDERME ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }

    printf("MESAJ GONDERME ISLEMI BASARILI!\n");

    //SUNUCUDAN GELECEK MESAJ ICIN HAFIZADAN YER AYIRMA ISLEMI
    char server_message[1024];
    memset(server_message, '\0', sizeof(server_message));

    //SUNUCUDAN MESAJI AL
    int receive_result;
    receive_result = recvfrom(socket_desc, server_message, sizeof(server_message), 0, (struct sockaddr*) &server_addr, &server_socklen);

    if(receive_result < 0){
        printf("HATA: MESAJ ALMA ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }

    printf("MESAJ ALMA ISLEMI BASARILI! Mesaj: %s", server_message);


    return EXIT_SUCCESS;
}