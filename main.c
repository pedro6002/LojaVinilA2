#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "clientes.h"
#include "discos.h"
#include "generos.h"
#include "locacoes.h"

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    menuClientes();
}
