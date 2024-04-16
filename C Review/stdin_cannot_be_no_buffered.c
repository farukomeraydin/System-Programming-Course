/*stdin dosyası işletim sistemlerinden dolayı genellikle default durumda ya da sonradan sıfır tamponlamalı moda sokulamamaktadır.Bu nedenle
Windows sistemlerinde ve UNIX / Linux sistemlerinde stdin satır tamponlamalıdır.Yani bir stdin dosyasından bir karaleter bile okumak istesek
eğer tampon doluysa bize bu karakter tampon verilir.Eğer tampon boş ise bizden bir satırlık bilgi istenir.Tampondaki satırın
sonunda '\n' karakteri de bulnmaktadır.Dolsyısıyla aşağıdaki kodda ikinci getchar klavyeden giriş beklemez.Tampondaki '\n' karakterini alarak
geri döner.*/
#include <stdio.h>

int main(void)
{
	int ch;

	ch = getchar();
	printf("%c (%d)", ch, ch);

	ch = getchar();
	printf("%c (%d)", ch, ch);

	return 0;
}
