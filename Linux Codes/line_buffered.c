//U/L'de default stdout satır tamponlamalıdır.Sonsuz for döngüsü yerine getchar() koyabilirdik ama isteğe bağlı olarak stdout'u flush edebiliyor.Windows'ta sıfır tamponlamalı olduğu için yazılır.
#include <stdio.h>

int main(void)
{
	printf("ankara"); //satır tamponlama olduğu için cache'e yazılır \n görünce write edilir.OS'in driver'ına aktarılmaz henüz.
	for (;;)
		;

	return 0;
}
