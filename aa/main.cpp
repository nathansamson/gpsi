#include <stdio.h>
#include <aalib.h>
aa_context *context;
int main()
{
  context = aa_autoinit(&aa_defparams);
  if(context == NULL) {
    fprintf(stderr,"Cannot initialize AA-lib. Sorry\n");
    return 1;
  }
  
while(true) {
 aa_puts(context, 0, 10, AA_BOLDFONT, "Azerty is cooler dan qwerty");
aa_putpixel(context,50,50, );
aa_render(context, 50, 50, 100, 100);
aa_flush(context);
}


  aa_close(context);
return 0;
}

