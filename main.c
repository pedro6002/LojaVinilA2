#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "clientes.h"

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    menuClientes();
}
