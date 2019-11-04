#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef struct{
    char actividad[100];
    int tiempo;
    int tipo; //0 = segundo, 1 = minuto, 2 = hora
}T_ACT;

void timer(void);
int ContarAct(FILE *fplan);
void MeterAct(FILE *fplan, T_ACT *vactividades, int n_act);
void Flow(T_ACT *vactividades, int n_act);

int main(void)
{
    FILE *fplan;
    T_ACT *vactividades;
    int n_act;
    int mode;
    
    do{
        printf("Elegir modo (1=duracion actividad||2=hora fin actividad)");
        scanf("%d",&mode);
        if(mode!=1&&mode!=2){
            printf("Modo no valido");
            system("PAUSE");
            system("cls");
        }
    }while(mode!=1&&mode!=2);
    
    if(mode==1){
        printf("===EJEMPLO DE FICHERO===");
        printf("\n[Nombre de actividad1] [timepo] [s|m|h]");
        printf("\n[Nombre de actividad3] [timepo] [s|m|h]");
        printf("\n[Nombre de actividad2] [timepo] [s|m|h]");
        printf("\n\nIMPORTANTE: SALVA EL FICHERO ANTES DE CONTINUAR\n\n");        
    }else{
        printf("===EJEMPLO DE FICHERO===");
        printf("\n[Nombre de actividad1] [hora en formato hhmm]");
        printf("\n[Nombre de actividad3] [hora en formato hhmm]");
        printf("\n[Nombre de actividad2] [hora en formato hhmm]");
        printf("\n\nIMPORTANTE: SALVA EL FICHERO ANTES DE CONTINUAR\n\n");
    }
    
    system("C:\\Users\\fcela\\Documents\\ICAI\\1\\Informatica\\TIMER\\Timer1_1\\Debug\\plan.txt");
    system("PAUSE");
    
    fplan = fopen("plan.txt","r+");
    if(fplan==NULL)
        printf("\nERROR: no se ha podido abrir el fichero plan.txt");
    else{
        
        if(mode==1)
            n_act = ContarAct(fplan);
        else
            n_act = ContarAct2(fplan);

        system("cls");
        
        if(n_act!=0){
            vactividades = (T_ACT *)calloc(n_act,sizeof(T_ACT));
            if(vactividades==NULL)
                printf("\nERROR: No se ha podido crear el vector");
            else{
                if(mode==1){
                    MeterAct(fplan,vactividades,n_act);
                    Flow(vactividades,n_act);                    
                }else{
                    //MeterAct2(fplan,vactividades,n_act);
                    //Flow2(vactividades,n_act);
                }
                
                
                //________________________________________________________________
                
                free(vactividades);
                printf("\n\n(vactividades cerrado)");
            }
        }else
            printf("\nERROR: fichero vacio");
    }
    
	printf("\n");
	return 0;
}

void timer(void)
{
    while(1>0){
        int t1 = time(NULL);
        printf("%d\n",t1);
        system("TIMEOUT /T 1 >NULL");
        system("cls");
    }
    
    return;
}

int ContarAct(FILE *fplan)
{
    int i=0, ctrl, b;
    char a[100];
    
    rewind(fplan);
    
    do{
        ctrl = fscanf(fplan,"%s %d %s\n",a, &b, a);
        if(ctrl==3)
            i++;
    }while(ctrl==3);
    
    return i;
}

int ContarAct2(FILE *fplan)
{
    int i=0, ctrl, b;
    char a[100];
    
    rewind(fplan);
    
    do{
        ctrl = fscanf(fplan,"%s %d\n",a, &b);
        if(ctrl==2)
            i++;
    }while(ctrl==2);
    
    return i;
}

void MeterAct(FILE *fplan, T_ACT *vactividades, int n_act)
{
    T_ACT act;
    int i,ctrl;
    int tiempo;
    char nombre[100], tipo[100];
    int len;
    
    rewind(fplan);
    
    for(i=0;i<n_act;i++){
        ctrl=fscanf(fplan,"%s %d %s", nombre, &tiempo, tipo);
        if(ctrl==3){
            len = strlen(nombre);
            if(nombre[len-1]=='\n')
                nombre[len-1]='\0';
            strcpy(act.actividad,nombre);
            act.tiempo=tiempo;
            if(tipo[0]=='h'||tipo[0]=='H')
                act.tipo=3600;
            else if(tipo[0]=='m'||tipo[0]=='M')
                act.tipo=60;
            else
                act.tipo=1;
            vactividades[i] = act;
            
        }
    }
    
    return;
}

void Flow(T_ACT *vactividades, int n_act)
{
    int ti = time(NULL), tiempo, i, j, t, trestante, trt;
    int tc;
    int tact;
    
    
    
    for(i=0;i<n_act;i++){
        tiempo=vactividades[i].tiempo*vactividades[i].tipo;
        tc = time(NULL);
        tact=tc+tiempo;
        
        while(tact-tc>0){
            tc = time(NULL);
            t = tact-tc;
            printf("TIEMPO TRANSCURRIDO: %02d:%02d:%02d\n",(tc-ti)/3600, ((tc-ti)/60)%60, (tc-ti)%60);
            printf("\nACTIVIDADES RESTANTES  TIEMPO");
            printf("\n====================== ========");
            trt=0;
            for(j=i+1;j<n_act;j++){
                trestante=vactividades[j].tiempo*vactividades[j].tipo;
                trt+=trestante;
                printf("\n%-21s %02d:%02d:%02d", vactividades[j].actividad, trestante/3600, (trestante/60)%60, trestante%60);
            }
            printf("\nTOTAL:                %02d:%02d:%02d", trt/3600, (trt/60)%60, trt%60);
            
            
            printf("\n\n     %s --> ",vactividades[i].actividad);
            if(t>3600)
                printf("%02d:%02d:%02d\n",t/3600, (t/60)%60, t%60);
            else if(t>60)
                printf("%02d:%02d\n",t/60,t%60);
            else
                printf("%2d\n",t);
            system("TIMEOUT /T 1 >NULL");
            system("cls");
        }
        Beep(750,750);
        Beep(1000,750);
        Beep(1500,1000);
    }
    return;
}