#include <efi.h>
#include <efilib.h>

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);

    Print(L"Maple UEFI Bootloader start\n");

    // 0x1000에 섹터 1~4 로드 (예시)
    VOID *loadAddr = (VOID *)0x1000;
    EFI_LBA startLBA = 1;
    UINTN numSectors = 4;

    EFI_BLOCK_IO_PROTOCOL *BlockIo;
    EFI_GUID BlockIoGUID = EFI_BLOCK_IO_PROTOCOL_GUID;

    // 블록 디바이스 프로토콜 검색
    EFI_STATUS status = uefi_call_wrapper(SystemTable->BootServices->LocateProtocol,
                                          3,
                                          &BlockIoGUID,
                                          NULL,
                                          (VOID **)&BlockIo);

    if (EFI_ERROR(status)) {
        Print(L"BlockIo locate failed: %r\n", status);
        return status;
    }

    // 섹터 읽기
    status = uefi_call_wrapper(BlockIo->ReadBlocks,
                               5,
                               BlockIo,
                               BlockIo->Media->MediaId,
                               startLBA,
                               numSectors * BlockIo->Media->BlockSize,
                               loadAddr);

    if (EFI_ERROR(status)) {
        Print(L"ReadBlocks failed: %r\n", status);
        return status;
    }

    // 0x2100에 1 저장
    *(volatile UINT64 *)0x2100 = 1;

    // Maple 부트로더로 점프 (섹터1 시작주소)
    void (*MapleMain)(void) = (void (*)(void))loadAddr;
    MapleMain();

    return EFI_SUCCESS;
}

