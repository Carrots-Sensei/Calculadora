#include "pch.h" // Inclusi�n de librer�as
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <math.h>
#include <Windows.h>

using namespace std;

// Declaraci�n de estructuras
typedef struct Operador 
{
	/* La idea de usar una pila para operadores se acompa�a de que exista una estructura que los represente.
	Esta estructura almacena un char que guarda el tipo de operador que aparece conforme se analiza el
	string (+,-,*,/,!,^). Posee punteros hacia otros elementos que le permiten crear una lista enlazada. */

	char Caracter;
	Operador *Anterior;
	Operador *Siguiente;
}*PtrOperador;
typedef struct Expresion
{
	/* Se ha visto conveniente que exista una segunda lista enlazada que posea de elementos cada uno de
	los caracteres de la operaci�n posfija, y para eso existe la presente estructura. Cuenta con un
	char que almacena el caracter, sea de tipo alfab�tico para las variables o un s�mbolo para los
	operadores. El atributo Valor se usa cuando el elemento representa una variable que siempre posee
	una cuantificaci�n num�rica. Posee punteros para la creaci�n de una lista enlazada. */

	char Caracter;
	float Valor;

	Expresion *Anterior;
	Expresion *Siguiente;
}*PtrExpresion;
typedef struct Operacion
{
	/* Se cre� en un comienzo para ser el tipo de estructura que se almacenar�a en un archivo f�sico (.txt), que
	pudiera recuperarse de la memoria para luego estructurar una lista enlazada que sirviera de historial de la
	calculadora. No pudo concretarse. Almacena dos strings, uno para la operaci�n infija y otro para la posfija,
	y un flotante para el resultado. Posee punteros para una lista enlazada. */

	string OperacionInfija;
	string OperacionPosfija;
	float Resultado;
	Operacion *Anterior;
	Operacion *Siguiente;
}*PtrOperacion;

// Funciones de inventario de operadores
void Inicializar_Inventario_Operador(PtrOperador &Lista)
{
	Lista = NULL; // Posiciona el puntero de la lista sobre NULL
}
PtrOperador Crear_Nuevo_Operador(char CaracterIngresando)
{
	/* Inicializa un nuevo elemento de la estructura */

	PtrOperador Nuevo_Operador = new(Operador); // Genera un nuevo dato del tipo Operador

	Nuevo_Operador->Caracter = CaracterIngresando; // Asigna un caracter ingresado
	Nuevo_Operador->Siguiente = NULL; // Punteros
	Nuevo_Operador->Anterior = NULL;

	return Nuevo_Operador; // Retorna el resultado
}
void Agregar_Inicio_Inventario_Operador(PtrOperador &Lista, PtrOperador &Nuevo)
{
	if (Lista != NULL) // Revisa si la lista se encuentra vac�a
	{
		Nuevo->Siguiente = Lista; // El nuevo elemento apunta al antiguo inicio de la lista
		Lista->Anterior = Nuevo; // El antiguo primer elemento apunta al nuevo primer elemento
		Lista = Nuevo; // El puntero de la lista se posiciona sobre el nuevo primer elemento
	}
	else // De estar vac�a...
	{
		Lista = Nuevo; // El puntero de la lista se posiciona sobre el elemento ingresado
	}

}
void Agregar_Final_Inventario_Operador(PtrOperador &Lista, PtrOperador &Nuevo)
{
	if (Lista != NULL) // Verifica si la lista se encuentra vac�a
	{
		PtrOperador Aux = Lista; // Se inicializa un puntero auxiliar

		while (Aux->Siguiente != NULL) // Se recorre la lista con el puntero auxiliar hasta encontrar el �ltimo elemento
		{
			Aux = Aux->Siguiente; // Se recorre la lista mientras se cumpla la condici�n planteada
		}
		Aux->Siguiente = Nuevo; // El antiguo �ltimo elemento apunta hacia el nuevo �ltimo elemento
		Nuevo->Anterior = Aux; // El nuevo �ltimo elemento apunta hacia el antiguo �ltimo elemento
	}
	else // De estar vac�a...
	{
		Lista = Nuevo; // El puntero de la lista se posiciona sobre el elemento ingresado
	}
}
void Listar_Inventario_Operador(PtrOperador Lista)
{
	if (Lista != NULL) // Verifica si la lista se encuentra vac�a
	{
		PtrOperador Aux = Lista; // Se inicializa un puntero auxiliar
		while (Aux != NULL) // Se recorre la lista hasta el final
		{
			cout << Aux->Caracter; // Se imprime un atributo
			Aux = Aux->Siguiente; // Se contin�a con el siguiente elemento
		}
		cout << endl << endl; // Formato
	}
	else // De estar vac�a...
	{
		cout << "No hay elementos para listar." << endl << endl;
	}
}

// Funciones de inventario de expresiones
void Inicializar_Inventario_Expresion(PtrExpresion &Lista)
{
	Lista = NULL; // Posiciona el puntero de la lista sobre NULL
}
PtrExpresion Crear_Nuevo_Expresion(char VariableOperando)
{
	/* Inicializa un nuevo elemento de la estructura */

	PtrExpresion NuevoExpresion = new(Expresion); // Genera un nuevo dato del tipo Expresion

	NuevoExpresion->Caracter = VariableOperando; // Asigna un caracter ingresado
	NuevoExpresion->Anterior = NULL; // Punteros
	NuevoExpresion->Siguiente = NULL;

	return NuevoExpresion; // Retorna el resultado
}
void Agregar_Inicio_Inventario_Expresion(PtrExpresion &Lista, PtrExpresion &Nuevo)
{
	if (Lista != NULL) // Revisa si la lista se encuentra vac�a
	{
		Nuevo->Siguiente = Lista; // El nuevo elemento apunta al antiguo inicio de la lista
		Lista->Anterior = Nuevo; // El antiguo primer elemento apunta al nuevo primer elemento
		Lista = Nuevo; // El puntero de la lista se posiciona sobre el nuevo primer elemento
	}
	else // De estar vac�a...
	{
		Lista = Nuevo; // El puntero de la lista se posiciona sobre el elemento ingresado
	}

}
void Agregar_Final_Inventario_Expresion(PtrExpresion &Lista, PtrExpresion &Nuevo)
{
	if (Lista != NULL) // Verifica si la lista se encuentra vac�a
	{
		PtrExpresion Aux = Lista; // Se inicializa un puntero auxiliar

		while (Aux->Siguiente != NULL) // Se recorre la lista con el puntero auxiliar hasta encontrar el �ltimo elemento
		{
			Aux = Aux->Siguiente; // Se recorre la lista mientras se cumpla la condici�n planteada
		}

		Aux->Siguiente = Nuevo; // El antiguo �ltimo elemento apunta hacia el nuevo �ltimo elemento
		Nuevo->Anterior = Aux; // El nuevo �ltimo elemento apunta hacia el antiguo �ltimo elemento
	}
	else // De estar vac�a...
	{
		Lista = Nuevo; // El puntero de la lista se posiciona sobre el elemento ingresado
	}
}
void Listar_Inventario_Expresion(PtrExpresion Lista)
{
	if (Lista != NULL) // Verifica si la lista se encuentra vac�a
	{
		PtrExpresion Aux = Lista; // Se inicializa un puntero auxiliar
		while (Aux != NULL) // Se recorre la lista hasta el final
		{
			cout << Aux->Caracter; // Se imprime un atributo
			Aux = Aux->Siguiente; // Se contin�a con el siguiente elemento
		}
		cout << endl << endl; // Formato
	}
	else // De estar vac�a...
	{
		cout << "No hay elementos para listar." << endl << endl;
	}
}
PtrExpresion Sacar_Inventario_Expresion_Anterior(PtrExpresion &Lista, PtrExpresion &ElementoReferencia)
{
	/* Se determin� conveniente que existira una funci�n que extr�llese de la lista enlazada un
	elemento previo a uno dado como referencia. */

	if (Lista != NULL) // Se verifica si la lista se encuentra vac�a
	{
		PtrExpresion Aux = Lista; // Se inicializa un puntero auxiliar

		while (Aux != NULL) // Se recorre la lista por completo
		{
			if (Aux->Siguiente == ElementoReferencia) // De encontrarse el elemento previo al dado por referencia...
			{
				PtrExpresion ElementoSiguiente = Aux->Siguiente; // Se accede a los punteros del elemento encontrado
				PtrExpresion ElementoAnterior = Aux->Anterior;

				if (ElementoSiguiente != NULL) // De existir un elemento en el puntero siguiente...
				{
					ElementoSiguiente->Anterior = ElementoAnterior; // Se interviene su puntero anterior...
				}
				if (ElementoAnterior != NULL) // De existir un elemento en el puntero anterior...
				{
					ElementoAnterior->Siguiente = ElementoSiguiente; // Se interviene su puntero siguiente...
				}

				Aux->Siguiente = NULL; // Se aterrizan los punteros del elemento encontrado
				Aux->Anterior = NULL;

				break; // Se detiene el ciclo
			}
			else // De no encontrarse el elemento deseado...
			{
				Aux = Aux->Siguiente; // Se prosigue con el siguiente
			}
		}

		return Aux; // Se retorna el valor del puntero auxiliar
	}
	else // De encontrarse vac�a la lista...
	{
		return NULL; // Se retorna NULL
	}
}

// Funciones de inventario de operaciones
void Inicializar_Inventario_Operacion(PtrOperacion &Lista)
{
	Lista = NULL; // Posiciona el puntero de la lista sobre NULL
}
PtrOperacion Crear_Nuevo_Operacion()
{
	/* Inicializa un nuevo elemento de la estructura */

	PtrOperacion NuevaOperacion = new(Operacion); // Genera un nuevo dato del tipo Operacion

	NuevaOperacion->OperacionInfija = ""; // Asignaci�n de atributos arbitrarios
	NuevaOperacion->OperacionPosfija = "";
	NuevaOperacion->Resultado = 0;

	NuevaOperacion->Anterior = NULL; // Punteros
	NuevaOperacion->Siguiente = NULL;

	return NuevaOperacion; // Retorna el resultado
}
void Agregar_Inicio_Inventario_Operacion(PtrOperacion &Lista, PtrOperacion &Nuevo)
{
	if (Lista != NULL) // Revisa si la lista se encuentra vac�a
	{
		Nuevo->Siguiente = Lista; // El nuevo elemento apunta al antiguo inicio de la lista
		Lista->Anterior = Nuevo; // El antiguo primer elemento apunta al nuevo primer elemento
		Lista = Nuevo; // El puntero de la lista se posiciona sobre el nuevo primer elemento
	}
	else // De estar vac�a...
	{
		Lista = Nuevo; // El puntero de la lista se posiciona sobre el elemento ingresado
	}
}
void Agregar_Final_Inventario_Operacion(PtrOperacion &Lista, PtrOperacion &Nuevo)
{
	if (Lista != NULL) // Verifica si la lista se encuentra vac�a
	{
		PtrOperacion Aux; // Inicializaci�n de un puntero auxiliar
		Aux = Lista; // Se asigna la direcci�n del puntero auxiliar al primer elemento de la colecci�n

		while (Aux->Siguiente != NULL) // Busca el �ltimo elemento en la colecci�n
		{
			Aux = Aux->Siguiente; // Se asigna la direcci�n del siguiente elemento
		}

		Aux->Siguiente = Nuevo; // La direcci�n del anterior �ltimo elemento cambia
		Nuevo->Anterior = Aux; // El nuevo �ltimo elemento apunta al anterior
	}
	else // De estar vac�a...
	{
		Lista = Nuevo; // El puntero de la lista se posiciona sobre el elemento ingresado
	}
}
void Listar_Inventario_Operacion(PtrOperacion Lista)
{
	if (Lista != NULL) // Se verifica si la lista se encuentra vac�a
	{
		PtrOperacion Aux = Lista; // Se inicializa un puntero auxiliar
		while (Aux != NULL) // Se recorre la lista hasta el final
		{
			cout << "Operacion Infija: " << Aux->OperacionInfija << endl; // Se imprimen atributos
			cout << "Operacion Posfija: " << Aux->OperacionPosfija << endl;
			cout << "Resultado: " << Aux->Resultado << endl << endl;
			Aux = Aux->Siguiente; // Se contin�a con el siguiente elemento
		}
		cout << endl << endl; // Formato
	}
	else // De estar vac�a...
	{
		cout << "No hay elementos para listar." << endl << endl;
	}
}
void Destruir_Inventario_Operacion(PtrOperacion &Lista)
{
	PtrOperacion Aux; // Inicializaci�n de un puntero auxiliar
	Aux = Lista; // El puntero auxiliar apunta hacia el comienzo de la colecci�n
	while (Aux != NULL) // Se recorre la colecci�n desde el comienzo
	{
		Lista = Lista->Siguiente; // Se asigna la direcci�n del nuevo elemento
		delete(Aux); // Se borra el contenido de la direcci�n contenida en el puntero auxiliar
		Aux = Lista; // Se asigna la direcci�n del siguiente elemento al puntero auxiliar
	}
}

// Funciones de pila de operadores
void Push_Operador(PtrOperador &Lista, PtrOperador &Nuevo)
{
	Agregar_Inicio_Inventario_Operador(Lista, Nuevo); // Se ingresa un nuevo elemento en el tope de la pila
}
PtrOperador Top_Operador(PtrOperador Lista)
{
	return Lista; // Se accede al tope de la lista
}
PtrOperador Pop_Operador(PtrOperador &Lista)
{
	if (Lista != NULL) // Verifica la existencia de elementos dentro de la lista
	{
		PtrOperador Aux = Lista; // Crea un puntero auxiliar
		Lista = Aux->Siguiente; // Cambia la direcci�n de Lista hacia el siguiente elemento
		Aux->Siguiente = NULL; // Redirecciona el puntero del elemento hacia NULL
		return Aux; // Regresa la direcci�n de un elemento aislado
	}
	else
	{
		cout << "No hay elementos para hacer POP." << endl << endl;
		return Lista;
	}
}

// Funciones de pila de expresiones
void Push_Expresion(PtrExpresion &Lista, PtrExpresion &Nuevo)
{
	Agregar_Inicio_Inventario_Expresion(Lista, Nuevo); // Se ingresa un nuevo elemento en el tope de la pila
}
PtrExpresion Top_Expresion(PtrExpresion Lista)
{
	return Lista; // Se accede al tope de la lista
}
PtrExpresion Pop_Expresion(PtrExpresion &Lista)
{
	PtrExpresion Aux = Lista; // Se inicializa un puntero auxiliar
	Lista = Lista->Siguiente; // Se redirecciona el comienzo de la pila
	Aux->Siguiente = NULL; // Se aisla el elemento por extraer
	return Aux; // Se retorna el resultado
}

// Funciones adicionales convenientes
float FuncionFactorial(float Valor) 
{
	if (Valor == 0 || Valor == 1) // Condiciones de parada
		return 1;
	else
		return(Valor*FuncionFactorial(Valor - 1)); // Caso de continuidad
}
int validarOpcionMenu(int valorMinimo, int ValorMaximo)
{
	/* Funci�n que verifica la entrada de datos v�lidos en un men� con m�ltiples opciones. */
	int opcion;
	while (true)
	{
		cout << "Ingresar una opcion valida: "; // Itera la instrucci�n hasta que sea un valor dentro de un rango establecido
		cin >> opcion;
		if ((opcion >= valorMinimo) && (opcion <= ValorMaximo))
		{
			break;
		}
	}
	return opcion; // Regresa un valor permitido
}

// Funciones de control de entrada
char SwitchLetras(char Letra)
{
	/* Funci�n que determina sin un caracter ingresado se corresponde con uno de la lista contenida en
	el switch o uno desconocido. Retorna un caracter resultado. */
	char Caracter;

	switch (Letra)
	{
	case '+':
	{
		Caracter = '+';
		break;
	}
	case '-':
	{
		Caracter = '-';
		break;
	}
	case '*':
	{
		Caracter = '*';
		break;
	}
	case '/':
	{
		Caracter = '/';
		break;
	}
	case '^':
	{
		Caracter = '^';
		break;
	}
	case '!':
	{
		Caracter = '!';
		break;
	}
	default:
	{
		Caracter = '?';
	}
	}

	return Caracter;
}
bool ContarParentesis(string Operacion)
{
	int NumParentesisApertura = 0;
	int NumParentesisCierre = 0;
	int Largo = Operacion.length(); // N�mero de caracteres de la expresi�n
	bool resultado = false; // Resultado de la funci�n

	for (int i = 0; i < Largo; i++) // Se recorre la expresi�n por completo
	{
		char Letra = Operacion[i]; // Se analiza el caracter de la posici�n i

		switch (Letra)
		{
		case '(': // Contabiliza el n�mero de par�ntesis de apertura de la expresi�n
		{
			NumParentesisApertura++;
			break;
		}
		case ')': // Contabiliza el n�mero de par�ntesis de cierre de la expresi�n
			NumParentesisCierre++;
			break;
		}
	}

	if ((NumParentesisApertura == NumParentesisCierre) && (NumParentesisApertura != 0) && (NumParentesisCierre != 0))
	{
		// Si el n�mero de par�ntesis de cierre y apertura coinciden se altera el resultado de la variable booleana
		resultado = true;
	}

	return resultado; // Se retorna el contenido de la variable
}
bool ContarOperadores(string Operacion)
{
	/* Por lo general, las expresiones de n operandos poseen n-1 operadores. */
	int Operandos = 0;
	int Operadores = 0;
	int Largo = Operacion.length(); // N�mero de caracteres de la expresi�n

	bool Condicion = false;

	for (int i = 0; i < Largo; i++) // Se recorre la expresi�n por completo
	{
		char Letra = Operacion[i]; // Caracter de la posici�n i

		if (isalpha(Letra) != 0) // De encontrar un operando...
		{
			Operandos++; // Aumenta el n�mero de operandos encontrados.
		}
		else // De encontrar un s�mbolo...
		{
			char Evaluando = SwitchLetras(Letra);

			if ((Evaluando != '?') && (Evaluando != '(') && (Evaluando != ')'))
			{
				Operadores++; // Se aumenta el n�mero de operadores
			}
			if (Evaluando == '!')
			{
				Operandos++; // Configuraci�n especial para el caso del factorial
			}
		}
	}

	if (Operandos - Operadores == 1) // Verifica la existencia de n operandos y n-1 operadores
	{
		Condicion = true;
	}

	return Condicion;
}
bool VerificarOperadores(string Operacion)
{
	bool Condicion = true;
	int Largo = Operacion.length(); // N�mero de caracteres de la expresi�n

	for (int i = 0; i < Largo; i++) // Recorre la expresi�n por completo
	{
		char Letra = Operacion[i]; // Caracter de la posici�n i
		char LetraSwitch = SwitchLetras(Letra);

		if (i < Largo - 1) // Caracteres anteriores al �ltimo
		{
			char Siguiente = Operacion[i + 1];
			char SiguienteSwitch = SwitchLetras(Siguiente);

			if ((Letra == '(') && (Siguiente == ')'))
			{
				// Caso donde se ingresan par�ntesis vac�os.
				Condicion = false;
				cout << "No se puede agregar parentesis que no tengan contenido." << endl;
			}
			if ((Letra == ')') && (Siguiente == '('))
			{
				// Caso donde se colocan grupos de par�ntesis sin separaci�n.
				Condicion = false;
				cout << "Los grupos de parentesis deben separarse por un operando." << endl;
			}
			if ((LetraSwitch != '?') && (SiguienteSwitch != '?'))
			{
				// Caso donde se colocan dos operandos sin separarse por un operador.
				Condicion = false;
				cout << "No se puede agregar dos operandos juntos." << endl;
			}
		}
		else // �ltimo caracter
		{
			if (Letra != ')')
			{
				Condicion = false;
				cout << "El ultimo caracter no puede ser diferente de un parentesis de cierre." << endl;
			}
		}
	}

	return Condicion;
}
bool VerificarEntrada(string Operacion)
{
	bool Resultado = false;

	bool Condicion1 = ContarParentesis(Operacion); // Se inicia un condicional para cada verificaci�n individual
	bool Condicion2 = ContarOperadores(Operacion);
	bool Condicion3 = VerificarOperadores(Operacion);

	if ((Condicion1 == true) && (Condicion2 == true) && (Condicion3 == true))
	{
		// Caso donde la expresi�n ingresada es completamente v�lida.
		Resultado = true;
	}
	if (Condicion1 == false)
	{
		cout << "El numero de parentesis de cierre debe ser igual al de apertura, ambos distintos de cero." << endl;
	}
	if (Condicion2 == false)
	{
		cout << "La suma de operadores nunca iguala o supera la de operandos." << endl;
	}

	return Resultado;
}

// Funciones de an�lisis y resoluci�n de string infijo
string OrdenarElementos(string Operacion, PtrExpresion &PilaExpresiones, PtrOperador &PilaOperadores)
{
	string CadenaPosfija; // String por modificarse
	int Largo = Operacion.length(); // Largo del string

	for (int i = 0; i < Largo; i++) // Se recorre el string por completo
	{
		char Letra = Operacion[i]; // Caracter de la posici�m i
		PtrOperador AuxOperador;
		PtrExpresion Aux = Crear_Nuevo_Expresion(Letra);

		if (isalpha(Letra) != 0) // Caracter de tipo alfab�tico
		{
			Agregar_Final_Inventario_Expresion(PilaExpresiones, Aux); // Se ingresa un operando en la lista de expresiones paralela
			CadenaPosfija += Letra; // Se ingresa el operando en la expresi�n posfija
		}
		else if (Letra == ')') // Par�ntesis de cierre
		{
			AuxOperador = Pop_Operador(PilaOperadores); // Extrae el elemento anterior de la pila, un operador.
			Aux->Caracter = AuxOperador->Caracter; // Se toma el caracter del operador.
			Agregar_Final_Inventario_Expresion(PilaExpresiones, Aux); // Se ingresa un operador en la lista paralela.

			Letra = Aux->Caracter;
			CadenaPosfija += Letra; // Se ingresa el operador en la expresi�n posfija
		}
		else // Todos los dem�s car�cteres
		{
			char LetraSwitch = SwitchLetras(Letra);

			if (Letra == '(') // Par�ntesis de apertura.
			{
				AuxOperador = Crear_Nuevo_Operador('(');
				Push_Operador(PilaOperadores, AuxOperador); // Se ingresa en la pila de operadores
			}
			else if (LetraSwitch != '?')
			{
				AuxOperador = Crear_Nuevo_Operador(Letra);
				Push_Operador(PilaOperadores, AuxOperador); // Se ingresa en la pila de operadores
			}
		}
	}

	return CadenaPosfija;
}
void SustituirVariables(PtrExpresion &PilaExpresiones)
{
	PtrExpresion Aux = PilaExpresiones;

	while (Aux != NULL) // Se recorre la lista de expresiones
	{
		char Letra = Aux->Caracter;

		if (isalpha(Letra) != 0) // Cuando se encuentra con un operando...
		{
			cout << "Ingrese el valor de la variable " << Letra << ": ";
			cin >> Aux->Valor; // Solicita su valor respectivo
		}
		Aux = Aux->Siguiente; // Contin�a con el siguiente elemento
	}
}
float ResolverOperacionParcial(PtrExpresion &Referencia, PtrExpresion Operando1, PtrExpresion Operando2)
{
	/* Se trata de un switch en donde se ingresan los valores necesarios para realizar cada
	una de las operaciones permitidas por la calculadora. Se realiza una u otra operaci�n
	seg�n indique la etiqueta del elemento de referencia, que siempre ha de ser un caracter
	de tipo operador. Es una subrutina de la funci�n ResolverOperacion. */

	char Operador = Referencia->Caracter;
	float resultado;

	switch (Operador)
	{
	case '+':
	{
		resultado = Operando1->Valor + Operando2->Valor;
		break;
	}
	case '-':
	{
		resultado = Operando2->Valor - Operando1->Valor;
		break;
	}
	case '*':
	{
		resultado = Operando1->Valor * Operando2->Valor;
		break;
	}
	case '/':
	{
		resultado = Operando2->Valor / Operando1->Valor;
		break;
	}
	case '^':
	{
		resultado = pow(Operando2->Valor, Operando1->Valor);
		break;
	}
	case '!':
	{
		resultado = FuncionFactorial(Operando1->Valor);
		break;
	}
	}

	return resultado;
}
void ResolverOperacion(PtrExpresion &PilaExpresiones)
{
	/* Funci�n de tipo recursivo. En cada ciclo se trabaja con una expresi�n de menor tama�o. Recorre
	los elementos de la lista enlazada paralela hasta encontrarse con un operador que, por la forma
	en que est� ideada la expresi�n posfija, se encuentra por delante de los dos operandos que resuelven
	su operaci�n. */

	if (PilaExpresiones != NULL) // Verifica si la lista se encuentra vac�a
	{
		PtrExpresion Aux = PilaExpresiones;
		bool Condicion = true;

		while (Condicion == true) // Busca la aparici�n del primer operador en la cadena posfija
		{
			char Letra = Aux->Caracter;

			if (isalpha(Letra) == 0) // Cuando se encuentra con un operador...
			{
				Condicion = false; // Detiene el ciclo
			}
			else // Cuando no...
			{
				Aux = Aux->Siguiente; // Contin�a con la b�squeda
			}
		}

		if (Aux->Caracter != '!') // Para el caso de operaciones diferentes al factorial...
		{
			// Se trabajan los dos elementos anteriores, que son extra�dos de la lista.
			PtrExpresion Operando1 = Sacar_Inventario_Expresion_Anterior(PilaExpresiones, Aux);
			PtrExpresion Operando2 = Sacar_Inventario_Expresion_Anterior(PilaExpresiones, Aux);

			/* El caracter de referencia (aux) pasar� a representar el resultado de la operaci�n que
			se resolvi� con los operandos anteriores. */

			if ((Operando1 != NULL) && (Operando2 != NULL))
			{
				Aux->Valor = ResolverOperacionParcial(Aux, Operando1, Operando2);
				Aux->Caracter = 'A'; // El caracter de refencia deja de ser un operador para convertirse en operando
			}
		}
		else // Para el caso de la operaci�n factorial
		{
			// Se trabaja con el elemento anterior
			PtrExpresion Operando1 = Sacar_Inventario_Expresion_Anterior(PilaExpresiones, Aux);

			/* El caracter de referencia (aux) pasar� a representar el resultado de la operaci�n que
			se resolvi� con el operando anterior. */
			if (Operando1 != NULL)
			{
				Aux->Valor = ResolverOperacionParcial(Aux, Operando1, NULL);
				Aux->Caracter = 'A'; // El caracter de refencia deja de ser un operador para convertirse en operando
			}
		}

		PilaExpresiones = Aux; // El puntero de la lista se posiciona sobre el nuevo operando

		if (PilaExpresiones->Siguiente != NULL)
		{
			/* Si no se ha resuelto la expresi�n, simplific�ndola en un solo operando/resultado, se procede a llamar
			nuevamente a la funci�n recursiva. */
			ResolverOperacion(PilaExpresiones);
		}
	}
}

// Programa principal
int main(int argc, char *argv[])
{
	// Inicializaci�n de Pilas
	PtrOperador PilaOperadores;
	PtrExpresion PilaExpresiones;
	PtrOperacion HistorialOperaciones;

	Inicializar_Inventario_Expresion(PilaExpresiones);
	Inicializar_Inventario_Operador(PilaOperadores);
	Inicializar_Inventario_Operacion(HistorialOperaciones);

	// Variables del men�
	bool Condicion = true;
	int Opcion;

	while (Condicion == true) // Men� de calculadora
	{
		system("cls");
		cout << endl;
		cout << "����������������������������������������������������������������������" << endl << endl;
		cout << "                          MENU PRINCIPAL" << endl;
		cout << "����������������������������������������������������������������������" << endl << endl;
		cout << "1. Instrucciones" << endl;
		cout << "2. Realizar operacion" << endl;
		cout << "3. Salir" << endl << endl;

		Opcion = validarOpcionMenu(1, 3);

		switch (Opcion)
		{
		case 1: // Instrucciones
		{
			system("cls");
			cout << endl;
			cout << "����������������������������������������������������������������������" << endl << endl;
			cout << "                          INSTRUCCIONES" << endl;
			cout << "����������������������������������������������������������������������" << endl << endl;
			cout << "Para utilizar la Calculadora Posfija primero se debe: " << endl; 
			cout << "1) Ingresar primero la operacion en formato infijo. " << endl;
			cout << "2) Sustituir los valores de cada variable cuando se solicite." << endl << endl;
			cout << "Buenas practicas para el manejo del programa son: " << endl;
			cout << "1) Hacer uso del abecedario en ingles unicamente." << endl;
			cout << "2) Ingresar cada operacion entre parentesis." << endl;
			cout << "3) Que el numero de parentesis de cierre y apertura coincidan." << endl;
			cout << "4) No ingresar parentesis que no tengan contenido." << endl;
			cout << "5) Cada grupo de parentesis debe separarse por un operador." << endl;
			cout << "6) El ultimo caracter debe ser un parentesis de cierre." << endl;
			cout << "7) No ingresar un menos (-) delante de ninguna expresion." << endl;
			cout << "Si se desea 'negar' el valor de un operando se debe ingresar negado." << endl << endl;
			cout << "Un ejemplo: " << endl;
			cout << "Ingrese una nueva operacion infija: (A+B)" << endl;
			cout << "La operacion posfija generada es: AB+" << endl << endl;
			cout << "Ingrese el valor de la variable A: 5" << endl;
			cout << "Ingrese el valor de la variable B: -5" << endl;
			cout << "El resultado de la operacion es: 0" << endl << endl;
			system("pause");
			break;
		}
		case 2: // Realizar operaci�n
		{
			system("cls");

			PtrOperacion Resolviendo = Crear_Nuevo_Operacion();
			Inicializar_Inventario_Operador(PilaOperadores);
			Inicializar_Inventario_Expresion(PilaExpresiones);

			cout << endl;
			cout << "����������������������������������������������������������������������" << endl << endl;
			cout << "                          OPERACION" << endl;
			cout << "����������������������������������������������������������������������" << endl << endl;
			cout << "Ingrese una nueva operacion infija: ";
			cin >> Resolviendo->OperacionInfija;
			cout << endl;

			// Se verifica que la expresi�n ingresada sea una v�lida.
			bool Proseguir = VerificarEntrada(Resolviendo->OperacionInfija);

			if (Proseguir == true)
			{
				Resolviendo->OperacionPosfija = OrdenarElementos(Resolviendo->OperacionInfija, PilaExpresiones, PilaOperadores);

				cout << "La operacion infija ingresa es: " << Resolviendo->OperacionInfija << endl;
				cout << "La operacion posfija generada es: " << Resolviendo->OperacionPosfija << endl << endl;

				SustituirVariables(PilaExpresiones);
				ResolverOperacion(PilaExpresiones);
				Resolviendo->Resultado = PilaExpresiones->Valor;

				cout << "El resultado de la operacion es: " << Resolviendo->Resultado << endl << endl;
			}
			else
			{
				cout << endl;
				cout << "Deben cumplirse las condiciones anteriores para realizarse la operacion." << endl << endl;
			}

			delete(Resolviendo);

			system("pause");
			break;
		}
		case 3: // Salir
		{
			Condicion = false;
			break;
		}
		}
	}

	// Calculadora con par�metros por l�nea de comando

	/* Para hacer uso de esta funci�n de la calculadora basta con ingresarse una operaci�n cualquiera por par�metro.
	No se requiere ingresar ning�n dato adicional. */
	if (argc != 2)
	{
		cout << endl << endl;
		cout << "El numero de argumentos de linea de comando debe ser 1.";
		cout << endl << endl;
		return 1;
	}

	system("cls");

	cout << "Se presenta a continuacion la operacion ingresada por argumentos de linea de comando: " << endl << endl;
	system("pause");

	PtrOperacion Resolviendo = Crear_Nuevo_Operacion();
	Inicializar_Inventario_Operador(PilaOperadores);
	Inicializar_Inventario_Expresion(PilaExpresiones);
	Resolviendo->OperacionInfija = argv[1];
	cout << endl;

	bool Proseguir = VerificarEntrada(Resolviendo->OperacionInfija);

	if (Proseguir == true)
	{
		Resolviendo->OperacionPosfija = OrdenarElementos(Resolviendo->OperacionInfija, PilaExpresiones, PilaOperadores);

		cout << "La operacion infija ingresa es: " << Resolviendo->OperacionInfija << endl;
		cout << "La operacion posfija generada es: " << Resolviendo->OperacionPosfija << endl << endl;

		SustituirVariables(PilaExpresiones);
		ResolverOperacion(PilaExpresiones);
		Resolviendo->Resultado = PilaExpresiones->Valor;

		cout << "El resultado de la operacion es: " << Resolviendo->Resultado << endl << endl;
	}
	else
	{
		cout << endl;
		cout << "Deben cumplirse las condiciones anteriores para realizarse la operacion." << endl << endl;
	}

	delete(Resolviendo);

	system("pause");

	return 0;
}