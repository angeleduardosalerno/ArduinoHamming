/*  El siguiente código enviará el mensaje 1010, codificado utilizando Hamming (paridad par) 
  La relación entre los bits del mensaje final y los pines de la placa es la siguiente:
  
  |-------|---|---|---|---|---|---|---|
  |pin    |2  |3  |4  |5  |6  |7  |8  |
  |-------|---|---|---|---|---|---|---|
  |bit    |P1 |P2 |D1 |P3 |D2 |D3 |D4 |
  |-------|---|---|---|---|---|---|---|
  
*/

int P1, P2, P3; //Declaro las variables que almacenan los bits de paridad. Se declaran 3 variables ya que con un mensaje de 4 bits, son necesarios 3 bits de paridad.
int D1=1, D2=0, D3=1, D4=0; //Declaro las variables que almacenan los bits de datos. Se declaran 4 variables, una para cada bit de datos.

void setup(){
  Serial.begin(9600); //Inicializo el puerto serie.
  
  /*  Configuro los pines de la arduino como salida.  */
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop(){
  /*  Calculo los bits de paridad en base a los bits de datos */
  P1 = (D1+D2+D4)%2; //Calculo para el bit de paridad 1.
  P2 = (D1+D3+D4)%2; //Calculo para el bit de paridad 2.
  P3 = (D2+D3+D4)%2; //Calculo para el bit de paridad 3.
  
  /*  Escribo cada uno de los bits en los correspondientes pines de la placa  */
  digitalWrite(2, P1);
  digitalWrite(3, P2);
  digitalWrite(4, D1);
  digitalWrite(5, P3);
  digitalWrite(6, D2);
  digitalWrite(7, D3);
  digitalWrite(8, D4);
  
  /*  Imprimo el mensaje por puerto serie */
  Serial.print(P1);
  Serial.print(P2);
  Serial.print(D1);
  Serial.print(P3);
  Serial.print(D2);
  Serial.print(D3);
  Serial.println(D4);
  
  delay(1000);
}
