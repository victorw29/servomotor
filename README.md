# Servo Motor PWM - Raspberry Pi Pico W

## Descrição
Este projeto controla um servomotor utilizando PWM no microcontrolador Raspberry Pi Pico W. A movimentação do servo é feita entre os ângulos de 0°, 90° e 180°, além de uma rotina de movimentação suave.

## Pinos Utilizados
- **Servo Motor**: GPIO 22
- **LED RGB**: GPIO 12

## Clonagem do Repositório
Para clonar este repositório, utilize o seguinte comando:
```sh
git clone https://github.com/victorw29/servomotor
```

## Compilação e Execução
1. Certifique-se de ter o Raspberry Pi Pico SDK configurado corretamente.
2. Crie um diretório de build e acesse-o:
   ```sh
   mkdir build && cd build
   ```
3. Execute o CMake para gerar os arquivos de compilação:
   ```sh
   cmake .. -G "Ninja"
   ```
4. Compile o projeto:
   ```sh
   ninja
   ```
5. Envie o binário gerado para o Raspberry Pi Pico:
   ```sh
   cp servomotor.uf2 /media/<USUARIO>/RPI-RP2
   ```

## Funcionamento
- O código define um sinal PWM na GPIO 22 para controlar a posição do servomotor.
- O servo passa por três posições fixas: 0°, 90° e 180°, aguardando 5 segundos em cada.
- Após isso, inicia-se uma movimentação suave entre 0° e 180° com incremento de 5µs e atraso de 10ms.

## Dependências
- Raspberry Pi Pico SDK
- CMake
- Ninja Build System

## Observações
- Se estiver usando o simulador Wokwi, pode ser necessário ajustar os tempos de espera devido ao comportamento do ambiente simulado.

  ## Links:
  - https://youtu.be/uvTaZiHFd3w
