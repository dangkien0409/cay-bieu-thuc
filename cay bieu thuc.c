#include <stdio.h>

// Định nghĩa cấu trúc nút cây
typedef struct Nut {
    char toan_tu;         // Lưu toán tử hoặc NULL nếu là toán hạng
    char toan_hang[10];   // Lưu toán hạng nếu là node lá (chuỗi để hỗ trợ cả số lẫn biến)
    struct Nut* trai;     // Con trái
    struct Nut* phai;     // Con phải
} Nut;

// Hàm tạo node lá (toán hạng)
Nut* taoNutLa(const char* gia_tri) {
    static Nut danh_sach_nut[100];  // Mảng tĩnh cho tối đa 100 nút
    static int so_nut = 0;          // Số nút hiện có
    Nut* nut = &danh_sach_nut[so_nut++];
    nut->toan_tu = '\0';            // Đây là nút lá, không có toán tử
    int i = 0;
    while (gia_tri[i] != '\0') {    // Sao chép chuỗi vào nút
        nut->toan_hang[i] = gia_tri[i];
        i++;
    }
    nut->toan_hang[i] = '\0';
    nut->trai = nut->phai = NULL;   // Không có con
    return nut;
}

// Hàm tạo node cha (toán tử)
Nut* taoNutCha(char toan_tu, Nut* trai, Nut* phai) {
    static Nut danh_sach_nut[100];
    static int so_nut = 0;
    Nut* nut = &danh_sach_nut[so_nut++];
    nut->toan_tu = toan_tu;
    nut->toan_hang[0] = '\0';  // Không có toán hạng
    nut->trai = trai;
    nut->phai = phai;
    return nut;
}

// Duyệt cây theo tiền tố
void duyetTienTo(Nut* goc) {
    if (goc != NULL) {
        if (goc->toan_tu != '\0') 
            printf("%c ", goc->toan_tu);  // In toán tử
        else 
            printf("%s ", goc->toan_hang);  // In toán hạng
        duyetTienTo(goc->trai);   // Duyệt cây con trái
        duyetTienTo(goc->phai);   // Duyệt cây con phải
    }
}

// Duyệt cây theo trung tố
void duyetTrungTo(Nut* goc) {
    if (goc != NULL) {
        duyetTrungTo(goc->trai);  // Duyệt cây con trái
        if (goc->toan_tu != '\0') 
            printf("%c ", goc->toan_tu);  // In toán tử
        else 
            printf("%s ", goc->toan_hang);  // In toán hạng
        duyetTrungTo(goc->phai);  // Duyệt cây con phải
    }
}

// Duyệt cây theo hậu tố
void duyetHauTo(Nut* goc) {
    if (goc != NULL) {
        duyetHauTo(goc->trai);  // Duyệt cây con trái
        duyetHauTo(goc->phai);  // Duyệt cây con phải
        if (goc->toan_tu != '\0') 
            printf("%c ", goc->toan_tu);  // In toán tử
        else 
            printf("%s ", goc->toan_hang);  // In toán hạng
    }
}

// Hàm chính
int main() {
    // Xây dựng cây biểu thức (a + 5*b/c - c^8 + d.e^0.5)
    Nut* goc = taoNutCha('+',
        taoNutCha('-',
            taoNutCha('+',
                taoNutLa("a"),
                taoNutCha('/',
                    taoNutCha('*', taoNutLa("5"), taoNutLa("b")),
                    taoNutLa("c")
                )
            ),
            taoNutCha('^', taoNutLa("c"), taoNutLa("8"))
        ),
        taoNutCha('*',
            taoNutLa("d"),
            taoNutCha('^', taoNutLa("e"), taoNutLa("0.5"))
        )
    );

    // Duyệt và in cây theo 3 cách
    printf("Duyệt tiền tố: ");
    duyetTienTo(goc);
    printf("\n");

    printf("Duyệt trung tố: ");
    duyetTrungTo(goc);
    printf("\n");

    printf("Duyệt hậu tố: ");
    duyetHauTo(goc);
    printf("\n");

    return 0;
}
