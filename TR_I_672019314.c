#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char file_name[] = "list_data.txt";
char delim[] = ";";
char data_barang[200][3][200];
int jml_data_barang = 0;
double total=0;
void struck(void);
void menu_utama(void);
void login(void);
void makananberat(void);
int harga_brg;
int i;

char *substring(char *string, int position, int length) {
   	char *pointer;
   	int c;
 
   	pointer = malloc(length+1);
   
   	if (pointer == NULL) {
      	printf("Unable to allocate memory.\n");
		exit(EXIT_FAILURE);
   	}
 
   	for (c = 0 ; c < length ; c++) {
      	*(pointer+c) = *(string+position-1);      
      	string++;  
   	}
 
   	*(pointer+c) = '\0';
 
   	return pointer;
}

void getData() {
	FILE *fp = fopen(file_name, "r");
    char line[200];
	
	memset(data_barang,0,sizeof(data_barang));
    jml_data_barang = 0;  
	   
	if (fp == NULL) {
		printf("Gagal membuka file %s", file_name);
		exit(EXIT_FAILURE);
	} else {
		int i = 0;
		while (fgets(line, sizeof(line), fp) != NULL) {
			char *token = strtok(line, delim);
    		
    		int j = 0;
			while (token != NULL) {
				strcpy(data_barang[i][j], token);
				token = strtok(NULL, delim);
				j++;
			}
			
			i++;
			jml_data_barang++;
		}
	}
	fclose(fp);
}

void viewData() {
    getData();
    system("@cls||clear");
    printf("============================================\n");
   	printf("\tMenu list  makanan\n");
   	printf("============================================\n");
   	
    if (jml_data_barang > 0) {
        printf("Nama Makanan\tHarga\tPorsi\n");
   		printf("============================================\n");
        
		for (i = 0; i < jml_data_barang; i++) {
			char nama_brg[100];
			strcpy(nama_brg, data_barang[i][0]);
			if (strlen(nama_brg) > 15) {
		   		strcpy(nama_brg, substring(nama_brg, 1, 15));
			} else if (strlen(nama_brg) < 8) {
		   		snprintf(nama_brg, sizeof nama_brg, "%s%s", data_barang[i][0], "\t");
			}
            int harga_brg = atoi(data_barang[i][1]);
            int stok_brg = atoi(data_barang[i][2]);

            printf("%s\t%d\t%d \n",nama_brg,harga_brg,stok_brg);
        }
    } else {
        printf("Tidak ada data barang!\n");
    }
    printf("============================================\n");
    system("pause");
    menu_utama();
}

bool addToFile(char inputan[]) {
	FILE *fp = fopen(file_name,"a+");
	if (fp == NULL) {
		return false;
	} else {
		fputs(inputan, fp);
	}
	fclose(fp);
	return true;
}

void tambahData() {
	scanf("%c");
	system("@cls||clear");
	printf("============================================\n");
   	printf("\tMenu Tambah list makanan\n");
   	printf("============================================\n");
   	
   	char nama[100], harga[50], stok[50], hasil[200];
   	
	printf("Masukkan Nama Barang : ");
   	gets(nama);
   	if (strlen(nama) > 15) {
   		strcpy(nama, substring(nama, 1, 15));
	}
	
   	printf("Masukkan Harga Barang : ");
   	gets(harga);
   	int hargaa = atoi(harga);
   	if (hargaa < 1000) hargaa = 1000;
   	else if (hargaa > 9999999) hargaa = 9999999;
   	
   	printf("Masukkan Stok Barang : ");
   	gets(stok);
   	int stokk = atoi(stok);
   	if (stokk < 1) stokk = 1;
   	else if (stokk > 10000) stokk = 10000;
   	
   	printf("============================================\n");
	snprintf(hasil, sizeof hasil, "%s;%d;%d;\n", nama, hargaa, stokk);
	if (addToFile(hasil)) {
		printf("Sukses tambah list makanan!\n");
	} else {
		printf("Gagal tambah list makanan!\n");
	}
	printf("============================================\n");
	system("pause");
    menu_utama();
}

void hapusData() {
	scanf("%c");
	system("@cls||clear");
	printf("============================================\n");
   	printf("Menu Hapus list Makanan\n");
   	printf("============================================\n");
   	char nama[100];
   	printf("Masukkan Nama Barang : ");
   	gets(nama);
	if (jml_data_barang > 0) {
		FILE *fp = fopen(file_name, "r");
	    char line[200];
		   
		if (fp == NULL) {
			printf("Gagal membuka file %s", file_name);
			exit(EXIT_FAILURE);
		} else {
			bool ada = false, ada2 = false;
			int i = 0, j = 0, k = 0;
			char tampung[100][200];
			while (fgets(line, sizeof(line), fp) != NULL) {
				char *token = strtok(line, delim);
	    		j = 0;
				ada = false;
				while (token != NULL) {
					if (j == 0) {
						if (strcmp(data_barang[i][j],nama) == 0) {
							ada = true;
							ada2 = true; //memastikan jika ketemu
						}
					}
					token = strtok(NULL, delim);
					j++;
				}
				
				if (!ada) {
					//data barang yg bukan dihapus akan ditampung di array tampung
					snprintf(tampung[k], sizeof tampung[k], "%s;%s;%s;\n", data_barang[i][0], data_barang[i][1], data_barang[i][2]);
					k++;
				}
				
				i++;
			}
			
			fclose(fp);
			
			printf("============================================\n");
			if (ada2) {
				fp = fopen(file_name, "w"); //reset file jadi kosong
				fclose(fp);
				if (k > 0) {
					for (i = 0; i < k; i++) {
						addToFile(tampung[i]);
					}	
				}
				printf("Sukses hapus (%s) dari data barang!\n",nama);
			} else {
				printf("Nama barang (%s) tidak ditemukan!\n",nama);
			}
		}
   	} else {
   		printf("============================================\n");
   		printf("Tidak ada data barang!\n");
    }
    
    printf("============================================\n");
    system("pause");
    menu_utama();
}
void transaksi(){
	int i, brng, pmbyr, kmbl, k2, hrg[100], jmlh[100], total=0, ttlhrg[100],tshd;
       char nama[100][30], p[5];
    scanf("%c");
	system("@cls||clear");
	printf("============================================\n");
   	printf("\t\tMenu Transaksi\n");
   	printf("============================================\n");
   int b;
			if (jml_data_barang > 0) {
        printf("Nama Makanan\tHarga\tPorsi\n");
   		printf("============================================\n");
        
		for (b = 0; b < jml_data_barang; b++) {
			char nama_brg[100];
			strcpy(nama_brg, data_barang[b][0]);
			if (strlen(nama_brg) > 15) {
		   		strcpy(nama_brg, substring(nama_brg, 1, 15));
			} else if (strlen(nama_brg) < 8) {
		   		snprintf(nama_brg, sizeof nama_brg, "%s%s", data_barang[b][0], "\t");
			}
            int harga_brg = atoi(data_barang[b][1]);
            int stok_brg = atoi(data_barang[b][2]);

            printf("%s\t%d\t%d \n",nama_brg,harga_brg,stok_brg);
        }
    } else {
        printf("Tidak ada data barang!\n");
    }
    printf("\n");
      printf("===-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-===\n");
      printf(": : Masukkan banyak Menu yang akan di pesan :  ");
      scanf("%i",&brng);
      for(i=1; i<=brng; i++)
     {
        printf(": : Masukkan nama daftar makanan ke-%i\t    : ",i);
        scanf("%s", &nama[i]);
        printf(": : Masukkan harga per makanan\t            : Rp. ");
        scanf("%i",&hrg[i]);
        printf(": : Masukkan jumlah porsi\t            : ");
        scanf("%i", &jmlh[i]);
        printf("\n");
        
     }
     printf("===-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
     for(i=1; i<=brng; i++)
     {
        ttlhrg[i]=jmlh[i]*hrg[i];
        total=total+ttlhrg[i];
     }
      printf("Total harga keseluruhan\t        : Rp. %i\n", total);
      printf("Masukkan jumlah pembayaran\t: Rp. ");
      scanf("%i,-", &pmbyr);
      kmbl=pmbyr-total;
      printf("===========================================\n");
      printf("Daftar pesanan anda:");
     for(i=1; i<=brng; i++)
     {
       printf("\n(%i). %i porsi %s (Rp.%i)\t: Rp.%i\n", i, jmlh[i], nama[i], hrg[i], ttlhrg[i]);
     }
     if(pmbyr>=total)
     {
        printf("Total harga\t\t: Rp. %i\n", total);
        printf("Pembayaran\t\t: Rp. %i\n", pmbyr);
        printf("Kembalian\t\t: Rp. %i\n", kmbl);
        time_t t;
	time(&t);
	printf("\nwaktu/hari : %s",ctime(&t));
	printf("\n");
     }
     else
     {
     	
        k2=-1*kmbl;
        printf("\n");
        printf("*******************************************\n");
        printf("\tTotal harga\t: Rp. %i\n", total);
        printf("\tPembayaran\t: Rp. %i\n", pmbyr);
        printf("\tKekurangan\t: Rp. %i\n", k2);
        printf("\n*******************************************");
        printf("\n\t\tMaaf Uang Anda Tidak Mencukupi\n");
        printf("\t Mohon Periksa Kembali Total Belanjaan Anda!\n");
        printf("Tekan (1) untuk kembali ke Transaksi...\n");
        system("pause");system("cls");
        transaksi();
     }
      printf("==============================================\n");
	  char name1[20];
	char name2[20];
	long long int phone;
	char address[40];
	char landmark[30];
	printf("Please Give Your Contact Details :\n");
	printf("NAMA DEPAN : ");
	scanf("%s",name1);
	printf("NAMA BELAKANG : ");
	scanf("%s",name2);
	printf("NO.HP : ");
	scanf("%lld",&phone);
	printf("ALAMAT : ");
	scanf("%s",address);
	printf("KOTA : ");
	scanf("%s",landmark);
	printf("\n\n");
	printf("data detailsnya sebagai berikut :\n");
	FILE *cust;
	cust = fopen("struck_data.txt","w");
	fprintf(cust,"Order Placed By : %s %s\nNo.hp : %lld\nalamat : %s\ntotal harga : %i\nPembayaran : %i\nkembalian : %i\n",name1,name2,phone,address,total,pmbyr,kmbl);
	fprintf(cust,"Your Order Will Be At Your Door In 30 minutes.\n");
	fprintf(cust," .....HAPPY ORDERING.....\n");
	fclose(cust);
	printf("  -->nama depan    :  %s\n  -->nama belakang :  %s\n  -->no.hp         :  %lld \n  -->alamat        :  %s \n  -->kota          :  %s \n",name1,name2,phone,address,landmark);
	printf("\n\n\n");
	printf("                       *********************************************************************************************\n");
	printf("                                             Your Order Will Be At Your Door In 30 minutes.\n");
	printf("                                                       .....HAPPY ORDERING.....\n");
	printf("                       *********************************************************************************************\n");
	 
	 printf("\nTekan (2) Untuk Kembali Ke Menu...\n");
     system("pause");system("cls");
	menu_utama();
      
	
}


void menu(int pil) {
	if (pil == 1) viewData();
	else if (pil == 2) tambahData();
	else if (pil == 3) hapusData();
	else if (pil == 4) transaksi();
}

void menu_utama() {
	int pilihan = 0;
	while (pilihan == 0) {
		system("@cls||clear");
		time_t t;
	time(&t);
	printf("                                                                                                         \n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t%s",ctime(&t));
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("===================================\n");
		printf("\t|");
		printf("WARTEG SEDERHANA|\n");
		printf("===================================\n");
		printf("|\t____________________\t  |\n");
		printf("|\t|  1. Lihat  Menu  |\t  |\n");
		printf("|\t|  2. Tambah Menu  |\t  |\n");
		printf("|\t|  3. Hapus  Menu  |\t  |\n");
		printf("|\t|  4. Transaksi    |\t  |\n");
		printf("|\t|  5. Logout       |\t  |\n");
		printf("|\t|  6. Exit         |\t  |\n");
		printf("|\t|__________________|\t  |\n");
		printf("|_________________________________|\n");
		printf("\tPilih Menu : ");
		scanf("%d",&pilihan);
		int tunggu;
		for( tunggu=0;tunggu<=50000;tunggu++)
	{
		printf("\r%d %% loading... ",tunggu/500);
	}
		if (pilihan <= 0 || pilihan > 6) {
			pilihan = 0;
			system("@cls||clear");
			printf("Pilihan Menu Salah!");
			system("pause");
		}
	}
	
	if (pilihan == 5) login();
	
	else  menu(pilihan);
}

void login() {
	int a=0,i=0;
    char uname[10],c=' '; 
    char password[10];
	system("@cls||clear");
	char username[20];
	printf("\t\t\t==================== LOGIN ====================\n");
	printf("                           Username(admin) : ");fflush(stdin);
	gets(username);
	
	printf("                           PIN(admin)      : ");fflush(stdin);
		while(i<10)
	{
	    password[i]=getch();
	    c=password[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	password[i]='\0';
	//char code=pword;
	i=0;
	
	if (strcmp(username,"yahya") == 0 && strcmp(password,"tagari") == 0) {
		int x;double y;
	 printf("\n");
   char salam[]=    "\t\t\t\t +-+AKSES DI TERIMA+-+ \n";
	
   printf("\n\n");
   for(x=0; salam[x]!=NULL; x++)
   {
     printf("%c",salam[x]);
      for(y=0; y<=9999999; y++)
      {
      }
   }
		printf("\n\t\t\t\tSelamat Datang %s!!!\n",username);
		system("pause"); system("cls");
		menu_utama();
	} else {
		printf("\t\t\t\nUsername/Password Salah!\n");
		scanf("%c");
		login();
	}
	
	
}

void main() {
	 int x;double y;
	 int tunggu;
   char salam[]=    "\t\t\t\t\t  SELAMAT DATANG DAN SELAMAT BERBELANJA";
	
   printf("\n\n\n");
   for(x=0; salam[x]!=NULL; x++)
   {
     printf("%c",salam[x]);
      for(y=0; y<=9999999; y++)
      {
      }
   }
   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
 
   for( tunggu=0;tunggu<=5000;tunggu++)
	{
		printf("\r%d %% loading... ",tunggu/500);
	}

	getData();
	login();
	menu_utama();
}


