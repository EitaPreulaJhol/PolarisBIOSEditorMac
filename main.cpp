#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cstdint>
#include <limits>

// Define 1 byte como o alinhamento para as estruturas:
#pragma pack(push, 1)


// Define algumas estruturas necessárias para manipular o arquivo:
struct ATOM_COMMON_TABLE_HEADER {
    int16_t usStructureSize;
    uint8_t ucTableFormatRevision;
    uint8_t ucTableContentRevision;
};

// Aqui estão as estruturas principais da BIOS:
struct ATOM_ROM_HEADER {
    ATOM_COMMON_TABLE_HEADER sHeader;
    uint8_t uaFirmWareSignature[4];
    uint16_t usBiosRuntimeSegmentAddress;
    uint16_t usProtectedModeInfoOffset;
    uint16_t usConfigFilenameOffset;
    uint16_t usCRC_BlockOffset;
    uint16_t usBIOS_BootupMessageOffset;
    uint16_t usInt10Offset;
    uint16_t usPciBusDevInitCode;
    uint16_t usIoBaseAddress;
    uint16_t usSubsystemVendorID;
    uint16_t usSubsystemID;
    uint16_t usPCI_InfoOffset;
    uint16_t usMasterCommandTableOffset;
    uint16_t usMasterDataTableOffset;
    uint8_t ucExtendedFunctionCode;
    uint8_t ucReserved;
    uint32_t ulPSPDirTableOffset;
    uint16_t usVendorID;
    uint16_t usDeviceID;
};

// E aqui estão as tabelas de dados:
struct ATOM_DATA_TABLES {
    ATOM_COMMON_TABLE_HEADER sHeader;
    uint16_t UtilityPipeLine;
    uint16_t MultimediaCapabilityInfo;
    uint16_t MultimediaConfigInfo;
    uint16_t StandardVESA_Timing;
    uint16_t FirmwareInfo;
    uint16_t PaletteData;
    uint16_t LCD_Info;
    uint16_t DIGTransmitterInfo;
    uint16_t SMU_Info;
    uint16_t SupportedDevicesInfo;
    uint16_t GPIO_I2C_Info;
    uint16_t VRAM_UsageByFirmware;
    uint16_t GPIO_Pin_LUT;
    uint16_t VESA_ToInternalModeLUT;
    uint16_t GFX_Info;
    uint16_t PowerPlayInfo;
    uint16_t GPUVirtualizationInfo;
    uint16_t SaveRestoreInfo;
    uint16_t PPLL_SS_Info;
    uint16_t OemInfo;
    uint16_t XTMDS_Info;
    uint16_t MclkSS_Info;
    uint16_t Object_Header;
    uint16_t IndirectIOAccess;
    uint16_t MC_InitParameter;
    uint16_t ASIC_VDDC_Info;
    uint16_t ASIC_InternalSS_Info;
    uint16_t TV_VideoMode;
    uint16_t VRAM_Info;
    uint16_t MemoryTrainingInfo;
    uint16_t IntegratedSystemInfo;
    uint16_t ASIC_ProfilingInfo;
    uint16_t VoltageObjectInfo;
    uint16_t PowerSourceInfo;
    uint16_t ServiceInfo;
};

// Header da tabela do PowerPlay:
struct ATOM_POWERPLAY_TABLE {
    ATOM_COMMON_TABLE_HEADER sHeader;
    uint8_t ucTableRevision;
    uint16_t usTableSize;
    uint32_t ulGoldenPPID;
    uint32_t ulGoldenRevision;
    uint16_t usFormatID;
    uint16_t usVoltageTime;
    uint32_t ulPlatformCaps;
    uint32_t ulMaxODEngineClock; // Max GPU Freq
    uint32_t ulMaxODMemoryClock; // Max Mem Freq
    uint16_t usPowerControlLimit;
    uint16_t usUlvVoltageOffset;
    uint16_t usStateArrayOffset;
    uint16_t usFanTableOffset;
    uint16_t usThermalControllerOffset;
    uint16_t usReserv;
    uint16_t usMclkDependencyTableOffset;
    uint16_t usSclkDependencyTableOffset;
    uint16_t usVddcLookupTableOffset;
    uint16_t usVddgfxLookupTableOffset;
    uint16_t usMMDependencyTableOffset;
    uint16_t usVCEStateTableOffset;
    uint16_t usPPMTableOffset;
    uint16_t usPowerTuneTableOffset;
    uint16_t usHardLimitTableOffset;
    uint16_t usPCIETableOffset;
    uint16_t usGPIOTableOffset;
    uint16_t usReserved[6];
};

// Tabela do PowerTune:
struct ATOM_POWERTUNE_TABLE {
    uint8_t ucRevId;
    uint16_t usTDP;
    uint16_t usConfigurableTDP;
    uint16_t usTDC;
    uint16_t usBatteryPowerLimit;
    uint16_t usSmallPowerLimit;
    uint16_t usLowCACLeakage;
    uint16_t usHighCACLeakage;
    uint16_t usMaximumPowerDeliveryLimit;
    uint16_t usTjMax;
    uint16_t usPowerTuneDataSetID;
    uint16_t usEDCLimit;
    uint16_t usSoftwareShutdownTemp;
    uint16_t usClockStretchAmount;
    uint16_t usTemperatureLimitHotspot;
    uint16_t usTemperatureLimitLiquid1;
    uint16_t usTemperatureLimitLiquid2;
    uint16_t usTemperatureLimitVrVddc;
    uint16_t usTemperatureLimitVrMvdd;
    uint16_t usTemperatureLimitPlx;
    uint8_t ucLiquid1_I2C_address;
    uint8_t ucLiquid2_I2C_address;
    uint8_t ucLiquid_I2C_Line;
    uint8_t ucVr_I2C_address;
    uint8_t ucVr_I2C_Line;
    uint8_t ucPlx_I2C_address;
    uint8_t ucPlx_I2C_Line;
    uint16_t usReserved;
};

// Tabela de controle das fans:
struct ATOM_FAN_TABLE {
    uint8_t ucRevId;
    uint8_t ucTHyst;
    uint16_t usTMin;
    uint16_t usTMed;
    uint16_t usTHigh;
    uint16_t usPWMMin;
    uint16_t usPWMMed;
    uint16_t usPWMHigh;
    uint16_t usTMax;
    uint8_t ucFanControlMode;
    uint16_t usFanPWMMax;
    uint16_t usFanOutputSensitivity;
    uint16_t usFanRPMMax;
    uint32_t ulMinFanSCLKAcousticLimit;
    uint8_t ucTargetTemperature;
    uint8_t ucMinimumPWMLimit;
    uint16_t usFanGainEdge;
    uint16_t usFanGainHotspot;
    uint16_t usFanGainLiquid;
    uint16_t usFanGainVrVddc;
    uint16_t usFanGainVrMvdd;
    uint16_t usFanGainPlx;
    uint16_t usFanGainHbm;
    uint16_t usReserved;
};

// Tabela de informações da VRAM:
struct ATOM_VRAM_INFO {
    ATOM_COMMON_TABLE_HEADER sHeader;
    uint16_t usMemAdjustTblOffset;
    uint16_t usMemClkPatchTblOffset;
    uint16_t usMcAdjustPerTileTblOffset;
    uint16_t usMcPhyInitTableOffset;
    uint16_t usDramDataRemapTblOffset;
    uint16_t usReserved1;
    uint8_t ucNumOfVRAMModule;
    uint8_t ucMemoryClkPatchTblVer;
    uint8_t ucVramModuleVer;
    uint8_t ucMcPhyTileNum;
};

// Entrada de informação da VRAM:
struct ATOM_VRAM_ENTRY {
    uint32_t ulChannelMapCfg;
    uint16_t usModuleSize;
    uint16_t usMcRamCfg;
    uint16_t usEnableChannels;
    uint8_t ucExtMemoryID;
    uint8_t ucMemoryType;
    uint8_t ucChannelNum;
    uint8_t ucChannelWidth;
    uint8_t ucDensity;
    uint8_t ucBankCol;
    uint8_t ucMisc;
    uint8_t ucVREFI;
    uint16_t usReserved;
    uint16_t usMemorySize;
    uint8_t ucMcTunningSetId;
    uint8_t ucRowNum;
    uint16_t usEMRS2Value;
    uint16_t usEMRS3Value;
    uint8_t ucMemoryVenderID;
    uint8_t ucRefreshRateFactor;
    uint8_t ucFIFODepth;
    uint8_t ucCDR_Bandwidth;
    uint32_t ulChannelMapCfg1;
    uint32_t ulBankMapCfg;
    uint32_t ulReserved;
    uint8_t strMemPNString[20];
};

// Tabela de timings da VRAM:
struct ATOM_VRAM_TIMING_ENTRY {
    uint32_t ulClkRange;
    uint8_t ucLatency[0x30];
};

// Fim do alinhamento das estruturas:
#pragma pack(pop)

// Helper para limpar o input:
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Template para solicitar valores ao usuário:
template<typename T>
T promptValue(const std::string& label, T currentValue, double multiplier = 1.0) {
    std::cout << label << " [Atual: " << (double)currentValue / multiplier << "]: ";
    double input;
    if (std::cin >> input) {
        return (T)(input * multiplier);
    } else {
        clearInput();
        return currentValue;
    }
}

// Classe principal do editor:
class PolarisEditor {
private:
    std::vector<uint8_t> buffer;
    
    // Pointers principais
    ATOM_ROM_HEADER* header = nullptr;
    ATOM_DATA_TABLES* data_table = nullptr;
    
    // PowerPlay Pointers
    int powerplay_offset = 0;
    ATOM_POWERPLAY_TABLE* pp_table = nullptr;
    ATOM_POWERTUNE_TABLE* powertune_table = nullptr;
    ATOM_FAN_TABLE* fan_table = nullptr;

    // VRAM Pointers
    int atom_vram_info_offset = 0;
    ATOM_VRAM_INFO* vram_info = nullptr;
    std::vector<ATOM_VRAM_TIMING_ENTRY*> timing_entries;

public:
    bool load(const std::string& filename) { // Carrega o arquivo BIOS
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file.is_open()) return false;
        
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        buffer.resize(size);
        if (!file.read((char*)buffer.data(), size)) return false;
        
        return parse();
    }
    
    bool parse() { // Analisa o buffer carregado
        if (buffer.size() < 0x80) return false;
        
        int master_ptr = 0x48;
        int header_offset = *(uint16_t*)&buffer[master_ptr];
        header = (ATOM_ROM_HEADER*)&buffer[header_offset];
        
        std::string sig((char*)header->uaFirmWareSignature, 4);
        if (sig != "ATOM") return false; // Verifica a assinatura "ATOM"
        
        data_table = (ATOM_DATA_TABLES*)&buffer[header->usMasterDataTableOffset];
        
        // Aqui começamos a configurar os ponteiros das tabelas necessárias
        powerplay_offset = data_table->PowerPlayInfo;
        pp_table = (ATOM_POWERPLAY_TABLE*)&buffer[powerplay_offset];
        
        // Nota: Offsets são relativos ao início da tabela PowerPlay
        powertune_table = (ATOM_POWERTUNE_TABLE*)&buffer[powerplay_offset + pp_table->usPowerTuneTableOffset];
        fan_table = (ATOM_FAN_TABLE*)&buffer[powerplay_offset + pp_table->usFanTableOffset];
        
        // Aqui configuramos os ponteiros da VRAM
        atom_vram_info_offset = data_table->VRAM_Info;
        vram_info = (ATOM_VRAM_INFO*)&buffer[atom_vram_info_offset];
        
        // Lógica para carregar as entradas de timing da VRAM
        int atom_vram_timing_offset = atom_vram_info_offset + vram_info->usMemClkPatchTblOffset + 0x2E;
        for (int i = 0; i < 48; i++) {
            int entry_offset = atom_vram_timing_offset + (i * sizeof(ATOM_VRAM_TIMING_ENTRY));
            if (entry_offset + sizeof(ATOM_VRAM_TIMING_ENTRY) > buffer.size()) break;
            ATOM_VRAM_TIMING_ENTRY* t_entry = (ATOM_VRAM_TIMING_ENTRY*)&buffer[entry_offset];
            if (t_entry->ulClkRange == 0) break;
            timing_entries.push_back(t_entry);
        }
        
        return true;
    }

    // Esse helper edita os valores do PowerTune:
    void editPowerTune() {
        std::cout << "\nPOWER TUNE (TDP/TDC)\n";
        powertune_table->usTDP = promptValue("TDP (W)", powertune_table->usTDP);
        powertune_table->usTDC = promptValue("TDC (A)", powertune_table->usTDC);
        powertune_table->usMaximumPowerDeliveryLimit = promptValue("Max Power Limit (W)", powertune_table->usMaximumPowerDeliveryLimit);
        powertune_table->usTjMax = promptValue("Max Temp (C)", powertune_table->usTjMax);
        powertune_table->usSoftwareShutdownTemp = promptValue("Shutdown Temp (C)", powertune_table->usSoftwareShutdownTemp);
        powertune_table->usTemperatureLimitHotspot = promptValue("Hotspot Temp (C)", powertune_table->usTemperatureLimitHotspot);
    }

    // Esse helper edita os valores do controle das fans:
    void editFan() {
        std::cout << "\nFAN CONTROL\n";
        fan_table->usTMin = promptValue("Min Temp (C)", fan_table->usTMin, 100.0);
        fan_table->usTMed = promptValue("Med Temp (C)", fan_table->usTMed, 100.0);
        fan_table->usTHigh = promptValue("High Temp (C)", fan_table->usTHigh, 100.0);
        fan_table->usTMax = promptValue("Max Temp (C)", fan_table->usTMax, 100.0);
        fan_table->ucTargetTemperature = promptValue("Temp Alvo (C)", fan_table->ucTargetTemperature);
        fan_table->usPWMMin = promptValue("Min PWM (%)", fan_table->usPWMMin, 100.0);
        fan_table->usFanPWMMax = promptValue("Max PWM (%)", fan_table->usFanPWMMax);
        fan_table->usFanRPMMax = promptValue("Max RPM", fan_table->usFanRPMMax);
        fan_table->ulMinFanSCLKAcousticLimit = promptValue("Limite Acustico (MHz)", fan_table->ulMinFanSCLKAcousticLimit, 100.0);
    }

    // Esse helper edita os clocks máximos da GPU e Memória, além do power limit:
    void editMaxClocks() {
        std::cout << "\nMAX CLOCKS (Limite do AMD Overdrive)\n";
        pp_table->ulMaxODEngineClock = promptValue("Max GPU Freq (MHz)", pp_table->ulMaxODEngineClock, 100.0);
        pp_table->ulMaxODMemoryClock = promptValue("Max Memory Freq (MHz)", pp_table->ulMaxODMemoryClock, 100.0);
        pp_table->usPowerControlLimit = promptValue("Power Control Limit (%)", pp_table->usPowerControlLimit);
    }
    
    void oneClickTimingPatch() {
        // Implementação simplificada do One Click Patch do PBE (UberMix 3.1).
        // Acho que ninguém vai usar isso em 2025, mas vai que né...
        const std::vector<uint8_t> uberMix31 = {
            0x77, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0xCC, 0x1C, 0x00, 0xAD, 0x61, 0x5C, 0x41, 
            0xC0, 0x59, 0x0E, 0x15, 0x2E, 0xCC, 0xA6, 0x0B, 0x00, 0x60, 0x07, 0x00, 0x0B, 0x03, 0x14, 0x20, 
            0xFA, 0x89, 0x00, 0xA0, 0x03, 0x00, 0x00, 0x00, 0x10, 0x12, 0x2F, 0x3F, 0xBA, 0x35, 0x40, 0x19
        };

        std::cout << "\nAplicando UberMix 3.1 >= 1750MHz...\n";
        int count = 0;
        for (auto* entry : timing_entries) {
            uint32_t mhz = (entry->ulClkRange & 0x00FFFFFF) / 100;
            if (mhz >= 1750) {
                std::memcpy(entry->ucLatency, uberMix31.data(), 48);
                count++;
            }
        }
        std::cout << "Modificados " << count << " straps.\n";
    }

    // Recalcula o checksum do BIOS:
    void fixChecksum() {
        int atom_rom_checksum_offset = 0x21;
        int size = buffer[0x02] * 512;
        
        buffer[atom_rom_checksum_offset] = 0;
        uint8_t offset_sum = 0;
        for (int i = 0; i < size; i++) offset_sum += buffer[i];
        buffer[atom_rom_checksum_offset] = (uint8_t)(0 - offset_sum);
        
        std::cout << "Checksum recalculado: 0x" << std::hex << (int)buffer[atom_rom_checksum_offset] << std::dec << "\n";
    }

    // Salva a BIOS modificada em um novo arquivo:
    bool save(const std::string& filename) {
        fixChecksum();
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;
        file.write((char*)buffer.data(), buffer.size());
        return true;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Uso: ./polarisbioseditormac <input.rom> <output.rom>\n";
        return 1;
    }

    PolarisEditor editor;
    if (!editor.load(argv[1])) {
        std::cerr << "Erro ao carregar o arquivo .rom\n";
        return 1;
    }

    // Menuzinho simples:
    int choice = 0;
    while (true) {
        std::cout << "\nPolarisBiosEditorMac\n\n";
        std::cout << "1. Editar PowerTune (TDP, TDC, Max Power)\n";
        std::cout << "2. Editar controle das Fans (Temps, PWM, RPM)\n";
        std::cout << "3. Editar clocks (GPU/Memorias)\n";
        std::cout << "4. Patch de timming das memorias (UberMix 3.1)\n";
        std::cout << "5. Salvar e sair\n";
        std::cout << "0. Sair sem salvar\n\n";
        std::cout << "Escolha: ";
        
        if (!(std::cin >> choice)) {
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: editor.editPowerTune(); break;
            case 2: editor.editFan(); break;
            case 3: editor.editMaxClocks(); break;
            case 4: editor.oneClickTimingPatch(); break;
            case 5: 
                if (editor.save(argv[2])) std::cout << "Arquivo salvo em: " << argv[2] << "\n";
                else std::cerr << "Erro ao salvar o arquivo.\n";
                return 0;
            case 0: return 0;
            default: std::cout << "Escolha invalida.\n";
        }
    }
}