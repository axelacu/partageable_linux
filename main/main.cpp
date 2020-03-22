
#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <string>


static int composant(int a, int b, char* lib, char* nom_compo)
{
        int (*compo)(int,int);
        int res = 0;
        void *handle;
        
        //std::cout << std::endl << "Loading Handler";
        // Ouverture de la bibliothèque
        
        handle = dlopen(lib , RTLD_LAZY);
      
        if(handle == NULL)
        {
                printf("erreur dlopen : %s\n", dlerror());
                exit(EXIT_FAILURE);
        }


        // Chargement de la fonction "func"
        *(void **) (&compo) = dlsym(handle, nom_compo);

        if (compo == NULL)
        {
                printf("Error occured");
                printf("erreur dlsym : %s\n", dlerror());
                dlclose(handle);
                exit(EXIT_FAILURE);
        }

        //exectuion
        res = compo(a,b);

        dlclose(handle);

        return res;
}
int main(int argc, char ** argv)
{
 
	int data1 = 1;
	int data2 = 2;

	int valeur1=0;
	int valeur2=0;

	char lib1[] = "./libComposant1.so";
	char lib2[] = "./libComposant2.so";
	
	char nom_compo1[] = "composant1";
	char nom_compo2[] = "composant2";

	valeur1 = composant(data1, data2, lib1, nom_compo1);
	valeur2 = composant(data1, data2, lib2, nom_compo2);

	std::cout << "Composant par chargement de librairie " <<  std::endl;

   std::cout << "valeur composant 1 :" << valeur1 << " valeur composant 2 :" << valeur2 << std::endl;
}

