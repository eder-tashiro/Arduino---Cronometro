Parola Scrolling Display - Timer Programável
Este projeto Arduino implementa um temporizador programável usando um display de matriz LED controlado pela biblioteca MD_Parola e MD_MAX72xx. O temporizador pode ser ajustado e controlado usando botões físicos e possui um alarme sonoro que toca quando o tempo se esgota.

Requisitos de Hardware
Arduino Uno ou compatível
Módulo de display de matriz LED de 4 segmentos (FC-16)
Buzzer ativo
3 botões de pressão (pull-up interno)
Resistores (se necessário)
Jumpers e protoboard
Conexões do Hardware
Display de Matriz LED:

CS_PIN (CS): Pino 10
DATA_PIN (DIN): Pino 11
CLK_PIN (CLK): Pino 13
Botões:

BUTTON_START: Pino 5
BUTTON_UP: Pino 4
BUTTON_DOWN: Pino 3
Buzzer:

buzzerPin: Pino 2
Instalação
Clone o Repositório:


git clone https://github.com/eder-tashiro/Arduino---Cronometro.git
Instale as Bibliotecas Necessárias:

Instale as bibliotecas MD_Parola e MD_MAX72xx através do Gerenciador de Bibliotecas do Arduino IDE.
Uso
Funcionalidade dos Botões
BUTTON_START (Pino 5):

Inicia o temporizador.
Se o temporizador estiver em execução, pausa ou retoma o temporizador.
BUTTON_UP (Pino 4):

Aumenta o tempo em 1 minuto. Funciona apenas quando o temporizador não está em execução.
BUTTON_DOWN (Pino 3):

Reseta o temporizador para o tempo inicial. Funciona apenas quando o temporizador está pausado ou não em execução.
Exibição e Controle de Tempo
O tempo restante é exibido no display LED em formato MM:SS.
Quando o tempo se esgota, um buzzer é ativado.
Exemplo de Uso
Pressione o botão START para iniciar o temporizador.
Use o botão UP para aumentar o tempo antes de iniciar.
Use o botão DOWN para resetar o temporizador enquanto ele está pausado ou parado.
Código-Fonte
O código principal é escrito em C++ utilizando o Arduino IDE. Ele implementa um temporizador programável que pode ser controlado através de botões físicos.


// Trecho de exemplo do código
void displayTime(unsigned long milliseconds) {
  unsigned int totalSeconds = milliseconds / 1000;
  unsigned int minutes = totalSeconds / 60;
  unsigned int seconds = totalSeconds % 60;

  sprintf(timeBuffer, "%02d:%02d", minutes, seconds);
  P.setTextBuffer(timeBuffer);
}
Contribuições
Contribuições são bem-vindas! Se você tiver sugestões de melhorias ou novos recursos, sinta-se à vontade para abrir uma issue ou um pull request.
