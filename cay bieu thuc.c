#include <stdio.h>

typedef struct Nut {
    char gia_tri[10];
    struct Nut* trai;
    struct Nut* phai;     
} Nut;

void saoChepChuoi(char* dich, const char* nguon) {
    while (*nguon) {
        *dich = *nguon;
        dich++;
        nguon++;
    }
    *dich = '\0';
}

Nut* taoNut(const char* gia_tri) {
    static Nut danh_sach_nut[100];
    static int chi_so_nut = 0;     
    Nut* nut_moi = &danh_sach_nut[chi_so_nut++]; 
    saoChepChuoi(nut_moi->gia_tri, gia_tri);     
    nut_moi->trai = NULL;
    nut_moi->phai = NULL;
    return nut_moi;
}

//tiền tố
void duyetTienTo(Nut* goc) {
    if (goc != NULL) {
        printf("%s ", goc->gia_tri); 
        duyetTienTo(goc->trai);    
        duyetTienTo(goc->phai);   
    }
}

// Trung tố
void duyetTrungTo(Nut* goc) {
    if (goc != NULL) {
        duyetTrungTo(goc->trai);     
        printf("%s ", goc->gia_tri); 
        duyetTrungTo(goc->phai);   
    }
}

//Hậu tố
void duyetHauTo(Nut* goc) {
    if (goc != NULL) {
        duyetHauTo(goc->trai);
        duyetHauTo(goc->phai);
        printf("%s ", goc->gia_tri);
    }
}

int main() {
    //(a + 5 * b / c - c^8 + d * e^0.5)
    Nut* goc = taoNut("+");

    // Cây con trái
    goc->trai = taoNut("-");
    goc->trai->trai = taoNut("+");
    goc->trai->trai->trai = taoNut("a");
    goc->trai->trai->phai = taoNut("/");
    goc->trai->trai->phai->trai = taoNut("*");
    goc->trai->trai->phai->trai->trai = taoNut("5");
    goc->trai->trai->phai->trai->phai = taoNut("b");
    goc->trai->trai->phai->phai = taoNut("c");
    goc->trai->phai = taoNut("^");
    goc->trai->phai->trai = taoNut("c");
    goc->trai->phai->phai = taoNut("8");

    // Cây con phải
    goc->phai = taoNut("*");
    goc->phai->trai = taoNut("d");
    goc->phai->phai = taoNut("^");
    goc->phai->phai->trai = taoNut("e");
    goc->phai->phai->phai = taoNut("0.5");

    // In 
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
