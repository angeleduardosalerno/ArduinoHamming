/*  El siguiente código recibirá el mensaje del receptor. El mensaje se encuentra codificado utilizando Hamming (paridad par), por lo tanto deberá decodificarse.
  La relación entre los bits del mensaje final y los pines de la placa es la siguiente:
  
  |-------|---|---|---|---|---|---|---|
  |pin    |2  |3  |4  |5  |6  |7  |8  |
  |-------|---|---|---|---|---|---|---|
  |bit    |P1 |P2 |D1 |P3 |D2 |D3 |D4 |
  |-------|---|---|---|---|---|---|---|
  
*/  

/*  Declaro las variables. A diferencia del emisor, el receptor no las inicializa con ningún valor particular, ya que los valores se 
 *  leeran de los pines de entrada 
 */
int P1, P2, D1, P3, D2, D3, D4;

void setup() {
  /*  Inicializo el puerto serie  */
  Serial.begin(9600);
  
  /*  Configuro los pines como entrada  */
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

}

void loop() {
  
  /*  Leo los valores de los pines y los asigno a las variables correspondientes  */
  P1 = digitalRead(2);
  P2 = digitalRead(3);
  D1 = digitalRead(4);
  P3 = digitalRead(5);
  D2 = digitalRead(6);
  D3 = digitalRead(7);
  D4 = digitalRead(8);

  /*  Imprimo por puerto serie los 7 bits recibidos */
  Serial.print("Recibido = ");
  Serial.print(P1);
  Serial.print(P2);
  Serial.print(D1);
  Serial.print(P3);
  Serial.print(D2);
  Serial.print(D3);
  Serial.println(D4);

  /*  Declaro variables para guardar los resultados del cálculo de paridad de los distintos grupos  */
  int grupo1 = (P1+D1+D2+D4)%2; //Calculo la paridad del grupo 1. (P1, D1, D2, D4)
  int grupo2 = (P2+D1+D3+D4)%2; //Calculo la paridad del grupo 2. (P2, D1, D3, D4)
  int grupo3 = (P3+D2+D3+D4)%2; //Calculo la paridad del grupo 3. (P3, D2, D3, D4)

  /*  Los 3 grupos representan la posición del bit erróneo en binario. El grupo 1, será el bit menos significativo, mientras que el 
   *  grupo 3 representará el bit más significativo. Sabiendo esto, estamos en condiciones de convertir dicho número binario a
   *  decimal, utilizando los 'pesos' binarios ( Bn*2^n + ... + B3*2^3 + B2*2^2 + B1*2^1 + B0*2^0 )
   */
  int posicionError = grupo3*4 + grupo2*2 + grupo1*1;

  if(posicionError!=0){
    Serial.print("Error en posicion = ");
    Serial.println(posicionError);
  }

  /*  Dado que los bits de datos se encuentran en las posiciones 3, 5, 6 y 7, de un mensaje codificado en Hamming, solamente }
   *  corregiremos un posible error allí. En las posiciones 1, 2 y 4, se encuentran los bits de paridad, en caso de error en 
   *  alguno de ellos, no nos interesará corregirlo ya que no forman parte del dato original.
   */
   switch(posicionError){
      case 3: //Si el error está en la posición 3, quiere decir que tenemos que corregir el bit de datos 1 (D1).
      if(D1==0) D1=1;
      else D1=0;
      break;

      case 5: //Si el error está en la posición 3, quiere decir que tenemos que corregir el bit de datos 2 (D2).
      if(D2==0) D2=1;
      else D2=0;
      break;

      case 6: //Si el error está en la posición 3, quiere decir que tenemos que corregir el bit de datos 3 (D3).
      if(D3==0) D3=1;
      else D3=0;
      break;
      
      case 7: //Si el error está en la posición 3, quiere decir que tenemos que corregir el bit de datos 4 (D4).
      if(D4==0) D4=1;
      else D4=0;
      break;
   }

   /* Imprimo por puerto serie el mensaje final (los bits de datos) */
   Serial.print("Mensaje = ");
   Serial.print(D1);
   Serial.print(D2);
   Serial.print(D3);
   Serial.println(D4);

  delay(1000);
}
