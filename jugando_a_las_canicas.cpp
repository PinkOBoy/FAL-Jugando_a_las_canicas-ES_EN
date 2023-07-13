/**
* @author PinkOBoy
*/
// LIBRARIES-----------------------------------------------------
#include <iostream>
#include <vector>
using namespace std;
// uncomment to read from a file instead of standard input
// descomentar en caso de querer leer la entrada por archivos en vez de por consola
// #include <fstream>

// TIPOS PERSONALIZADOS------------------------------------------
// TYPEDEFS
/*
* Compactamos los datos del jugador y sus canicas en un solo tipo de dato
* para no tener que generar más parámetros en las funciones y que sea más
* fácil de entender.
*/
/*
* By using a datatype for both player and player's marbles information, it's
* more intuitive for us to manage the data: we use less input parameters in
* the algorithm and operations gets easier to understand.
*/
struct tJugador {
	string name;
	int canicas;
};

// PROTOTIPOS----------------------------------------------------
// PROTOTYPES

// En esta funcion, la posicion final esta fuera del vector: [ini;fin)
// In this function, the end position is placed outside the vector: [ini; fin)
tJugador resolver(
	const vector<tJugador>& jugadores, // jugadores + canicas // players + marbles
	int inicio, // posicion de inicio del vector visible // start position of the visible vector
	int fin // posicion de fin del vector visible // end position of the visible vector
);

// En esta funcion, la posicion final esta incluido en el vector: [ini;fin]
// In this function, the end position is included in the vector: [ini; fin]
tJugador resolver2(
	const vector<tJugador>& jugadores,
	int inicio,
	int fin
);

// MAIN----------------------------------------------------------
bool solve() {
	// read case
	/*
	* The boolean value of cin indicates if the last read was successful.
	* You need to read something before checking it.
	* 
	* El valor booleano dentro de cin indica si la ultima lectura fue posible.
	* Hay que leer algo antes de hacer comprobaciones con ello.
	*/
	int n;

	cin >> n;
	if (!cin)
		return false;

	vector<tJugador> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i].name >> v[i].canicas;

	// compute solution

	tJugador r = resolver(v, 0, n);
	//tJugador m = resolver2(v, 0 , n-1);

	// write solution

	cout << r.name << ' ' << r.canicas << endl;
	//cout << m.name << ' ' << m.canicas << endl;

	return true;
}

int main() {
	// uncomment to read from a file instead of standard input
	// ifstream ifs("sample.in");
	// cin.rdbuf(ifs.rdbuf());

	while (solve());
	return 0;
}

// IMPLEMENTACION------------------------------------------------
// IMPLEMENTATION

// SPANISH-------------------------------------------------------
/* ECUACIONES DE RECURRENCIA:
* Observamos que nuestro problema coge el tamaño original
* del problema y lo va reduciendo en subproblemas mas pe
* queños de menor tamaño.
*
* Dada la generalizacion de las ecuaciones de recurrencia
* de algoritmos recursivos y el estudio de su coste, sabemos
* que la ecuacion de recurrencia de un algoritmo recursivo
* donde se reduce el tamaño del problema, es:
*
*		| c0				0 <= n <= n0
*	T(n)	|
*		| a * T(n / b) + c1 * n^k	n0 <= n
*
* Donde:
*	n ::= el tamaño del problema en la llamada actual
*	a ::= numero de llamadas recursivas dentro del algoritmo
*	b ::= elementos quitados del tamaño del problema
*	k ::= numero tal que n^k representa la complejidad del codigo no recursivo del algoritmo
*
* Aplicandolo a nuestro caso particular, si definimos:
*
*	n::= tamaño del vector visible en la llamada actual
*
* Concluimos que la ecuacion de recurrencia es:
*
*		| c0				n = 1
*	T(n)	|
*		| 2 * T(n / 2) + c1 * n^0 	n > 1
*/
/* COMPLEJIDAD DEL ALGORITMO:
* Dada la generalizacion de las ecuaciones de recurrencia de
* algoritmos recursivos y el estudio de coste, sabemos que
* bajo las condiciones del problema, y con los datos anteriores,
* la complejidad del algoritmo seguira la siguiente regla:
*
*	a < b^k -> T(n) pertenece a O(n ^ k)
*	a = b^k -> T(n) pertenece a 0(n^k * ln(n))
*	a > b^k -> T(n) pertenece a O(n ^ logb(a))
*
* Efectivamente, en nuestro caso 2 > 2^0 = 1, por lo tanto:
*
*	T(n) pertenece a O(n ^ log2(2)) = O(n)
*/

// ENGLISH-------------------------------------------------------
/* RECURRENCE EQUATIONS
* For every call, the size of the problem gets halved,
* that is, in each call does some calculations (O(1)) on a number
* of one digit lesser than the previous call.
*
* Defining:
*
*   n::= number of elements of the visible subvector from v.
*
* We know, thanks to the Generalitation techniques for recursive
* algorithms, that, in case the problem gets reduced in a specific
* amount of data (a constant is subtracted from thesize of the problem
* in each call), its recurrence equations will be:
*
*        | c0                       0 <= n <= n0
*   T(n)=|
*        | a * T(n / b) + c1 * n^k  n >= n0
*
* Where:
*
*   a::= number of recursive calls inside of the algorithm.
*   b::= subtrahend
*   k::= a number so n^k represents the complexity of the non-recursive code
*        of our algorithm.
*
* Therefore, we can affirm that the recurrence equations of our algorithm are:
*
*          | c0                         n = 1
*    T(n)= |
*          | 2 * T(n / 2) + c1 * n^0    n > 1
*/
/* COMPLEXITY OF THE ALGORITHM
 * Thanks to the previosly defined information and to the Generalitation
 * techniques for recursive algorithms, we know that, when the recurrence
 * equations look like:
 *
 *        | c0                       0 <= n <= n0
 *   T(n)=|
 *        | a * T(n / b) + c1 * n^k  n >= n0
 *
 * The following assumptions are correct:
 *
 *  a < b^k -> T(n) belongs to O(n ^ k)
 *  a = b^k -> T(n) belongs to O(n^k * ln(n))
 *  a > b^k -> T(n) belongs to O(n ^ logb(a))
 *
 * Applying it to our recurrence equations:
 *
 *  2 > 2^0
 *
 * Therefore, T(n) belongs to O(n ^ log2(2)) = O(n).
*/

tJugador resolver(
	const vector<tJugador>& v,
	int ini,
	int fin
) {
	// CASO BASE // DIRECT CASE
	// Hemos encontrado a un jugador para los primeros duelos
	// We've found a player for the firsts duels
	if (ini + 1 == fin)
		return v[ini];

	// CASO RECURSIVO // RECURSIVE CASE
	else {
		// Solucion hallada en esta llamada // Soluntion found on this call
		tJugador solFinal;
		// mediatriz del vector visible // bisector of the visible vector
		int mediatriz = (ini + fin) / 2;

		/* - SPANISH ---------------------------------------------------------
		* Para hallar al campeon, tenemos que saber quienes van ganando los
		* duelos.
		* 
		*		 1	-			   - 5
		*			  |-----	 --------|
		*		 2	-	 |	|	   - 6
		*				 | -::-	|
		*		 3	-	 |    	|	   - 7
		*			  |-----	 ---------|
		*		 4	-			   - 8
		* 
		* Podemos entender que, para encontrar a los jugadores para el duelo
		* actual, necesitamos saber quien ha ganado los duelos anteriores. Al
		* dividir a los jugadores en parejas y con ayuda del esquema, podemos
		* llamar a esos duelos anteriores como el "duelo de la izquierda" que
		* nos darán un ganador, y el "duelo de la derecha" que nos dará otro.
		* 
		*		Ganador_izquierda -
		*				   |- Ganador_siguiente
		*    	  	Ganador_derecha --
		* 
		* Ademas, vemos que esta division de izquierda y derecha nos sirve
		* tanto para un duelo concreto, como para todo el torneo o un 
		* subconjunto de duelos.
		* 
		* Dado que por cada duelo hay dos jugadores, necesitaremos 2 llamadas
		* recursivas para hallarlos: una para la parte "izquierda" de los
		* jugadores, y otra para la parte "derecha" de los jugadores
		* 
		* Con eso, reducimos el tamaño del problema en cada llamada a la mitad.
		* 
		* El campeon sera aquel jugador que gane todos los duelos en los que
		* participe.
		*/
		/* - ENGLISH -------------------------------------------------------------
		* To find the champion, we have to know which players are winning the
		* duels.
		* 
		*		 1	-			   - 5
		*			  |-----	 --------|
		*		 2	-	 |	|	   - 6
		*				 | -::-	|
		*		 3	-	 |    	|	   - 7
		*			  |-----	 ---------|
		*		 4	-			   - 8
		* 
		* Its understandable to say that, to find the players for the current
		* duel, we need to know the players who have won the previous duels. The
		* tournament divides the players in pairs (thanks to the exercise instructions
		* and that sketch). So, the "left duels" will give us one winner and the
		* "right duels" will give us another one.
		* 
		*		 Left_Winner -
		*				|- Next_Winner
		*    		Right_Winner -
		* 
		* By knowing that each duel is composed by two players, we'll need
		* 2 recursive calls to find them: one for the "left" side of the players
		* in the vector; the other for the "right" side.
		* 
		* By this, the size of the problem gets halved for each call.
		* 
		* The champion will be the player who wins every duel they participates.
		*/

		tJugador solIzq = resolver(v, ini, mediatriz);
		tJugador solDer = resolver(v, mediatriz, fin);

		// Con estos datos, decidimos el ganador de este duelo
		// With this data, we decide the winner of this duel

		if (solIzq.canicas >= solDer.canicas) {
			solFinal = solIzq;
			solFinal.canicas += solDer.canicas / 2;
		} else {
			solFinal = solDer;
			solFinal.canicas += solIzq.canicas / 2;
		}

		// Devolvemos el ganador a la anterior llamada
		// We return the winner to the previous call

		return solFinal;
	}
}

tJugador resolver2(
	const vector<tJugador>& v,
	int ini,
	int fin
) {
	// CASO BASE // DIRECT CASE
	if (ini + 1 == fin)
		return v[ini];

	// CASO RECURSIVO // RECURSIVE CASE
	else {
		tJugador solFinal;
		int mediatriz = (ini + fin) / 2;

		tJugador solIzq = resolver2(v, ini, mediatriz);
		tJugador solDer = resolver2(v, mediatriz + 1, fin);
		/*
		* Si no añadimos el +1, estariamos analizando 2 veces
		* la posición v[mediatriz]. Eso rompe el algoritmo. Da
		* una solucion erronea o una recursion infinita.
		*/
		/*
		* If we don't write that +1, the program would analyze the
		* player v[bisector] 2 times. That breaks the algorithm.
		* It'll return a wrong solution or generate an infinite
		* recurrence.
		*/

		if (solIzq.canicas >= solDer.canicas) {
			solFinal = solIzq;
			solFinal.canicas += solDer.canicas / 2;
		}
		else {
			solFinal = solDer;
			solFinal.canicas += solIzq.canicas / 2;
		}

		return solFinal;
	}
}
