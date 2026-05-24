
#include <iostream>
#include <xlsxwriter.h>

int main() {
    // Excelファイル作成
    lxw_workbook  *workbook  = workbook_new("sample.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    // データ書き込み
    worksheet_write_string(worksheet, 0, 0, "商品名", nullptr);
    worksheet_write_string(worksheet, 0, 1, "価格", nullptr);
    worksheet_write_string(worksheet, 1, 0, "りんご", nullptr);
    worksheet_write_number(worksheet, 1, 1, 120, nullptr);
    worksheet_write_string(worksheet, 2, 0, "ばなな", nullptr);
    worksheet_write_number(worksheet, 2, 1, 80, nullptr);

    worksheet_write_string(worksheet, 3, 0, "tea", nullptr);
    worksheet_write_number(worksheet, 3, 1, 110, nullptr);

    // ファイル保存
    workbook_close(workbook);

    return 0;
}
