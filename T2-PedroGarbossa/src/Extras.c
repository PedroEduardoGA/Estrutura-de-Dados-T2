#include <stdio.h>
#include "Extras.h"

char* CodigoExposicao(double Radiacao)
{
    if(Radiacao <= 25)
        return "#00ffff";

    if(Radiacao <= 50)
        return "#00ff00";

    if(Radiacao <= 100)
        return "#ff00ff";

    if(Radiacao <= 250)
        return "#0000ff";

    if(Radiacao <= 600)
        return "#800080";

    if(Radiacao <= 1000)
        return "#000080";

    if(Radiacao <= 8000)
        return "#ff0000";
    
    return "#000000";//caso seja maior que 8000
}