# PolarisBIOSEditorMac

Um editor simples da BIOS das placas da série AMD Polaris, porém, para macOS. 
Permite modificar parâmetros de power, fan control, clock limits e memory timings diretamente do arquivo ROM da BIOS. 
Ferramenta similar ao PolarisBiosEditor.


## O que pode ser alterado:

- **Power Tune**: Editar TDP, TDC, limites de potência máxima e temperaturas
- **Fan Control**: Configurar pontos de temperatura, PWM e RPM das ventoinhas
- **Max Clocks**: Modificar limites de overdrive da GPU e memória
- **Memory Timings**: Aplicar patches de timings de memória (UberMix 3.1)


## Estruturas Suportadas:

O editor trabalha com as seguintes estruturas da BIOS ATOM:
- `ATOM_ROM_HEADER` - Header principal da BIOS
- `ATOM_DATA_TABLES` - Tabelas de dados do firmware
- `ATOM_POWERPLAY_TABLE` - Tabelas de power/performance
- `ATOM_POWERTUNE_TABLE` - Configurações de TDP/TDC
- `ATOM_FAN_TABLE` - Configurações de controle das fans
- `ATOM_VRAM_INFO` e `ATOM_VRAM_TIMING_ENTRY` - Informações de VRAM


## Requisitos:

- C++17 ou superior
- Compilador Clang ou GCC
- Arquivo ROM válido de GPU AMD Polaris


## Como compilar:

Use o seguinte comando para compilar:

```bash
clang++ -std=c++17 -o polarisbioseditormac main.cpp
```


## Como usar:

```bash
./polarisbioseditormac <input.rom> <output.rom>
```


⚠️ **Aviso**: Modificar a BIOS pode danificar sua GPU. Sempre faça backup do arquivo ROM original antes de usar este editor.