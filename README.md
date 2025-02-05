
  # Projeto de Temporizadores com Pico SDK
   
    Este repositório contém dois projetos desenvolvidos em C para o microcontrolador Raspberry Pi Pico W.
 
  ## Atividade 1: Temporizador Periódico (Semáforo)
  - Utiliza um temporizador periódico para alternar LEDs (vermelho, amarelo e verde) a cada 3 segundos.
  - Exibe mensagens a cada 1 segundo via porta serial.
  
  ## Atividade 2: Temporizador de Um Disparo (One-Shot)
  - LEDs são acionados por um botão e desligam gradualmente a cada 3 segundos.
  - O botão só pode ser pressionado novamente após o último LED apagar.
  - Implementação de debounce opcional.
  
  ## Como rodar o projeto
  1. Instale o Pico SDK e configure o ambiente no VS Code.
  2. Compile o código e envie para o Raspberry Pi Pico.
  3. Utilize o Wokwi para simulação, se necessário.
  4. Acompanhe as mensagens via porta serial para depuração.
  
  ## Estrutura do Repositório
  - `atv1_semaforo.c`: Código da Atividade 1
  - `atv2_temporizador_oneshot.c`: Código da Atividade 2
  - `README.md`: Este arquivo com instruções
  
  ## Autor
  - Andressa Peixoto Nonato
 
