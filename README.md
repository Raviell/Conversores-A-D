# Conversores-A-D

# Projeto ADC PWM Joystick - RP2040

## Descrição
Este projeto utiliza um microcontrolador RP2040 para controlar LEDs RGB via PWM e exibir a posição de um joystick em um display OLED SSD1306. As entradas do joystick são lidas por conversores analógico-digitais (ADC), e os botões são gerenciados por interrupções (IRQ) com debounce.

## Componentes Utilizados
- RP2040 (Raspberry Pi Pico)
- Joystick analógico (conectado aos pinos ADC 26 e 27)
- LEDs RGB (conectados aos pinos 11, 12 e 13 via PWM)
- Display OLED SSD1306 (conectado via I2C nos pinos 14 e 15)
- Botão do joystick (conectado ao pino 22)
- Botão adicional (conectado ao pino 5)

## Funcionalidades
- O eixo **X** do joystick controla o brilho do **LED Vermelho**.
- O eixo **Y** do joystick controla o brilho do **LED Azul**.
- O **botão do joystick** alterna o LED Verde e altera o estilo da borda do display.
- O **botão A** ativa/desativa os LEDs PWM.
- O quadrado no **display OLED** se move de acordo com a posição do joystick.

## Estrutura do Código
```
/Projeto_ADC_Pico
│── CMakeLists.txt
│── main.c
│── ssd1306.c
│── ssd1306.h
│── joystick.c
│── joystick.h
│── pwm_led.c
│── pwm_led.h
│── irq.c
│── irq.h
│── debouncing.c
│── debouncing.h
│── README.md
```

## Configuração e Compilação
### Dependências
- [Pico SDK](https://github.com/raspberrypi/pico-sdk)
- Biblioteca para **SSD1306** (implementada no projeto)

### Passos para Compilar e Rodar
1. Configure o **Pico SDK**.
2. Clone este repositório.
3. No terminal, execute:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
4. Transfira o arquivo `.uf2` para o Raspberry Pi Pico.
5. Conecte o hardware e teste as funcionalidades.

## Contribuição
Pull requests são bem-vindos! Para mudanças maiores, abra uma issue primeiro para discutir o que deseja modificar.

