/* Uses every function in cpdflibwrapper.h */
#include <stdbool.h>
#include <stdio.h>

#include "cpdflibwrapper.h"

void prerr(void) {
  if (cpdf_lastError > 0)
    printf("(%i | %s)\n", cpdf_lastError, cpdf_lastErrorString);
  cpdf_clearError();
}

int main(int argc, char **argv) {
  /* CHAPTER 0. Preliminaries */
  printf("***** CHAPTER 0. Preliminaries\n");
  printf("---cpdf_startup()\n");
  cpdf_startup(argv);
  prerr();
  printf("---cpdf_version()\n");
  printf("version = %s\n", cpdf_version());
  prerr();
  printf("---cpdf_setFast()\n");
  cpdf_setFast();
  prerr();
  printf("---cpdf_setSlow()\n");
  cpdf_setSlow();
  prerr();
  printf("---cpdf_clearError()\n");
  cpdf_clearError();
  prerr();
  // printf("---cpdf_onExit()\n");
  // cpdf_onExit();

  /* CHAPTER 1. Basics */
  printf("***** CHAPTER 1. Basics\n");
  printf("---cpdf_fromFile()\n");
  int f = cpdf_fromFile("cpdflibmanual.pdf", "");
  prerr();
  printf("---cpdf_fromFileLazy()\n");
  int f2 = cpdf_fromFileLazy("cpdflibmanual.pdf", "");
  prerr();
  int buflen;
  printf("---cpdf_toMemory()\n");
  void *buf = cpdf_toMemory(f, false, false, &buflen);
  printf("---cpdf_fromMemory()\n");
  int frommem = cpdf_fromMemory(buf, buflen, "");
  cpdf_toFile(frommem, "testoutputs/01fromMemory.pdf", false, false);
  prerr();
  printf("---cpdf_fromMemoryLazy()\n");
  int frommemlazy = cpdf_fromMemoryLazy(buf, buflen, "");
  prerr();
  cpdf_toFile(frommemlazy, "testoutputs/01fromMemoryLazy.pdf", false, false);
  cpdf_deletePdf(f);
  prerr();
  cpdf_replacePdf(f2, frommem);
  prerr();
  printf("---cpdf: enumerate PDFs\n");
  int numpdfs = cpdf_startEnumeratePDFs();
  prerr();
  for (int x = 0; x < numpdfs; x++) {
    int key = cpdf_enumeratePDFsKey(x);
    prerr();
    char *info = cpdf_enumeratePDFsInfo(x);
    prerr();
  }
  cpdf_endEnumeratePDFs();
  prerr();
  printf("---cpdf_ptOfIn()\n");
  printf("One inch is %f points\n", cpdf_ptOfIn(1.0));
  prerr();
  printf("---cpdf_ptOfCm()\n");
  printf("One centimetre is %f points\n", cpdf_ptOfCm(1.0));
  prerr();
  printf("---cpdf_ptOfMm()\n");
  printf("One millimetre is %f points\n", cpdf_ptOfMm(1.0));
  prerr();
  printf("---cpdf_inOfPt()\n");
  printf("One point is %f inches\n", cpdf_inOfPt(1.0));
  prerr();
  printf("---cpdf_cmOfPt()\n");
  printf("One point is %f centimetres\n", cpdf_cmOfPt(1.0));
  prerr();
  printf("---cpdf_mmOfPt()\n");
  printf("One point is %f millimetres\n", cpdf_mmOfPt(1.0));
  prerr();
  printf("---cpdf_range()\n");
  int range = cpdf_range(1, 5);
  prerr();
  printf("---cpdf_all()\n");
  int range_all = cpdf_all(f2);
  prerr();
  printf("---cpdf_even()\n");
  int range_even = cpdf_even(range_all);
  prerr();
  printf("---cpdf_odd()\n");
  int range_odd = cpdf_odd(range_all);
  prerr();
  printf("---cpdf_rangeUnion()\n");
  int range_union = cpdf_rangeUnion(range, range_all);
  prerr();
  printf("---cpdf_difference()\n");
  int range_difference = cpdf_difference(range, range_all);
  prerr();
  printf("---cpdf_removeDuplicates()\n");
  int range_remove_dups = cpdf_removeDuplicates(range_all);
  prerr();
  printf("---cpdf_rangeLength()\n");
  int range_length = cpdf_rangeLength(range_all);
  prerr();
  printf("---cpdf_rangeGet()\n");
  int range_get = cpdf_rangeGet(range_all, 0);
  prerr();
  printf("---cpdf_rangeAdd()\n");
  int range_add = cpdf_rangeAdd(range_all, 20);
  prerr();
  printf("---cpdf_isInRange()\n");
  int range_is_in_range = cpdf_isInRange(range_all, 5);
  prerr();
  printf("---cpdf_parsePagespec()\n");
  int rfrompagespec = cpdf_parsePagespec(f2, "1-3,end");
  prerr();
  printf("---cpdf_validatePagespec()\n");
  printf("Validating pagespec gives %i\n", cpdf_validatePagespec("1-4,5,6"));
  prerr();
  printf("---cpdf_stringOfPagespec()\n");
  printf("String of pagespec is %s\n", cpdf_stringOfPagespec(f2, range));
  prerr();
  printf("---cpdf_blankRange()\n");
  int br = cpdf_blankRange();
  prerr();
  printf("---cpdf_pages()\n");
  printf("Pages = %i\n", cpdf_pages(f2));
  prerr();
  printf("---cpdf_pagesFast()\n");
  printf("Pages = %i\n", cpdf_pagesFast("", "cpdflibmanual.pdf"));
  prerr();
  printf("---cpdf_toFile()\n");
  int fout = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_toFile(fout, "testoutputs/01tofile.pdf", false, false);
  prerr();
  printf("---cpdf_toFileExt()\n");
  cpdf_toFileExt(fout, "testoutputs/01tofileext.pdf", false, true, true, true,
                 true);
  cpdf_deletePdf(f2);
  cpdf_deletePdf(fout);
  prerr();
  int f3 = cpdf_fromFile("cpdflibmanual.pdf", "");
  printf("---cpdf_isEncrypted()\n");
  printf("isencrypted:%i\n", cpdf_isEncrypted(f3));
  prerr();
  printf("---cpdf_isLinearized()\n");
  printf("islinearized:%i\n", cpdf_isLinearized("cpdflibmanual.pdf"));
  printf("---cpdf_toFileEncrypted()\n");
  int permissions = {cpdf_noEdit};
  int encmethod = cpdf_pdf40bit;
  cpdf_toFileEncrypted(f3, encmethod, &permissions, 1, "owner", "user", false,
                       false, "testoutputs/01encrypted.pdf");
  prerr();
  printf("---cpdf_toFileEncryptedExt()\n");
  cpdf_toFileEncryptedExt(f3, encmethod, &permissions, 1, "owner", "user",
                          false, false, true, true, true,
                          "testoutputs/01encryptedext.pdf");
  prerr();
  cpdf_deletePdf(f3);
  int pdfenc = cpdf_fromFile("testoutputs/01encrypted.pdf", "user");
  printf("---cpdf_hasPermission()\n");
  printf("Haspermission %i, %i\n", cpdf_hasPermission(pdfenc, cpdf_noEdit),
         cpdf_hasPermission(pdfenc, cpdf_noCopy));
  prerr();
  printf("---cpdf_encryptionKind()\n");
  printf("encryption kind is %i\n", cpdf_encryptionKind(pdfenc));
  prerr();
  printf("---cpdf_decryptPdf()\n");
  cpdf_decryptPdf(pdfenc, "user");
  prerr();
  printf("---cpdf_decryptPdfOwner()\n");
  int pdfenc3 = cpdf_fromFile("testoutputs/01encrypted.pdf", "");
  cpdf_decryptPdfOwner(pdfenc3, "owner");
  prerr();
  printf("---cleaning up");
  cpdf_deletePdf(frommemlazy);
  cpdf_deletePdf(pdfenc);
  cpdf_deletePdf(pdfenc3);
  cpdf_deleteRange(range);
  cpdf_deleteRange(range_all);
  cpdf_deleteRange(range_even);
  cpdf_deleteRange(range_odd);
  cpdf_deleteRange(range_union);
  cpdf_deleteRange(range_difference);
  cpdf_deleteRange(range_remove_dups);
  cpdf_deleteRange(range_length);
  cpdf_deleteRange(range_get);
  cpdf_deleteRange(range_add);
  cpdf_deleteRange(range_is_in_range);
  cpdf_deleteRange(rfrompagespec);
  cpdf_deleteRange(br);

  /* CHAPTER 2. Merging and Splitting */
  printf("***** CHAPTER 2. Merging and Splitting\n");
  int mergepdf = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pdfs[] = {mergepdf, mergepdf, mergepdf};
  printf("---cpdf_mergeSimple()\n");
  int merged = cpdf_mergeSimple(pdfs, 3);
  prerr();
  cpdf_toFile(merged, "testoutputs/02merged.pdf", false, false);
  printf("---cpdf_merge()\n");
  int merged2 = cpdf_merge(pdfs, 3, false, false);
  prerr();
  cpdf_toFile(merged2, "testoutputs/02merged2.pdf", false, false);
  int a = cpdf_all(mergepdf);
  int b = cpdf_all(mergepdf);
  int c = cpdf_all(mergepdf);
  int ranges[] = {a, b, c};
  printf("---cpdf_mergeSame()\n");
  int merged3 = cpdf_mergeSame(pdfs, 3, false, false, ranges);
  prerr();
  cpdf_toFile(merged3, "testoutputs/02merged3.pdf", false, false);
  printf("---cpdf_selectPages()\n");
  int range_select = cpdf_range(1, 3);
  int selected = cpdf_selectPages(mergepdf, range_select);
  prerr();
  cpdf_toFile(selected, "testoutputs/02selected.pdf", false, false);
  cpdf_deletePdf(mergepdf);
  cpdf_deletePdf(merged);
  cpdf_deletePdf(merged2);
  cpdf_deletePdf(merged3);
  cpdf_deletePdf(selected);
  cpdf_deleteRange(a);
  cpdf_deleteRange(b);
  cpdf_deleteRange(c);
  cpdf_deleteRange(range_select);

  /* CHAPTER 3. Pages */
  printf("***** CHAPTER 3. Pages\n");
  int pagespdf1 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf2 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf3 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf4 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf5 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf6 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf7 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf8 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf9 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf10 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf11 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf12 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf13 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf14 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf15 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf16 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf17 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf18 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int pagespdf19 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int r3 = cpdf_all(pagespdf1);
  printf("---cpdf_scalePages()\n");
  cpdf_scalePages(pagespdf1, r3, 1.5, 1.8);
  prerr();
  cpdf_toFile(pagespdf1, "testoutputs/03scalepages.pdf", false, false);
  printf("---cpdf_scaleToFit()\n");
  cpdf_scaleToFit(pagespdf2, r3, 1.5, 1.8, 0.9);
  prerr();
  cpdf_toFile(pagespdf2, "testoutputs/03scaletofit.pdf", false, false);
  printf("---cpdf_scaleToFitPaper()\n");
  cpdf_scaleToFitPaper(pagespdf3, r3, cpdf_a4portrait, 0.8);
  prerr();
  cpdf_toFile(pagespdf3, "testoutputs/03scaletofitpaper.pdf", false, false);
  printf("---cpdf_scaleContents()\n");
  struct cpdf_position p = {
      .cpdf_anchor = cpdf_topLeft, .cpdf_coord1 = 20, .cpdf_coord2 = 20};
  cpdf_scaleContents(pagespdf4, r3, p, 2.0);
  prerr();
  cpdf_toFile(pagespdf4, "testoutputs/03scalecontents.pdf", false, false);
  printf("---cpdf_shiftContents()\n");
  cpdf_shiftContents(pagespdf5, r3, 1.5, 1.25);
  prerr();
  cpdf_toFile(pagespdf5, "testoutputs/03shiftcontents.pdf", false, false);
  printf("---cpdf_rotate()\n");
  cpdf_rotate(pagespdf6, r3, 90);
  prerr();
  cpdf_toFile(pagespdf6, "testoutputs/03rotate.pdf", false, false);
  printf("---cpdf_rotateBy()\n");
  cpdf_rotateBy(pagespdf7, r3, 90);
  prerr();
  cpdf_toFile(pagespdf7, "testoutputs/03rotateby.pdf", false, false);
  printf("---cpdf_rotateContents()\n");
  cpdf_rotateContents(pagespdf8, r3, 35.0);
  prerr();
  cpdf_toFile(pagespdf8, "testoutputs/03rotatecontents.pdf", false, false);
  printf("---cpdf_upright()\n");
  cpdf_upright(pagespdf9, r3);
  prerr();
  cpdf_toFile(pagespdf9, "testoutputs/03upright.pdf", false, false);
  printf("---cpdf_hFlip()\n");
  cpdf_hFlip(pagespdf10, r3);
  prerr();
  cpdf_toFile(pagespdf10, "testoutputs/03hflip.pdf", false, false);
  printf("---cpdf_vFlip()\n");
  cpdf_vFlip(pagespdf11, r3);
  prerr();
  cpdf_toFile(pagespdf11, "testoutputs/03vflip.pdf", false, false);
  printf("---cpdf_crop()\n");
  cpdf_crop(pagespdf12, r3, 0.0, 0.0, 400.0, 500.0);
  prerr();
  cpdf_toFile(pagespdf12, "testoutputs/03crop.pdf", false, false);
  printf("---cpdf_trimMarks()\n");
  cpdf_trimMarks(pagespdf13, r3);
  prerr();
  cpdf_toFile(pagespdf13, "testoutputs/03trim_marks.pdf", false, false);
  printf("---cpdf_showBoxes()\n");
  cpdf_showBoxes(pagespdf14, r3);
  prerr();
  cpdf_toFile(pagespdf14, "testoutputs/03show_boxes.pdf", false, false);
  printf("---cpdf_hardBox()\n");
  cpdf_hardBox(pagespdf15, r3, "/MediaBox");
  prerr();
  cpdf_toFile(pagespdf15, "testoutputs/03hard_box.pdf", false, false);
  printf("---cpdf_removeCrop()\n");
  cpdf_removeCrop(pagespdf16, r3);
  prerr();
  cpdf_toFile(pagespdf16, "testoutputs/03remove_crop.pdf", false, false);
  printf("---cpdf_removeTrim()\n");
  cpdf_removeTrim(pagespdf17, r3);
  prerr();
  cpdf_toFile(pagespdf17, "testoutputs/03remove_trim.pdf", false, false);
  printf("---cpdf_removeArt()\n");
  cpdf_removeArt(pagespdf18, r3);
  prerr();
  cpdf_toFile(pagespdf18, "testoutputs/03remove_art.pdf", false, false);
  printf("---cpdf_removeBleed()\n");
  cpdf_removeBleed(pagespdf19, r3);
  prerr();
  cpdf_toFile(pagespdf19, "testoutputs/03remove_bleed.pdf", false, false);
  cpdf_deletePdf(pagespdf1);
  cpdf_deletePdf(pagespdf2);
  cpdf_deletePdf(pagespdf3);
  cpdf_deletePdf(pagespdf4);
  cpdf_deletePdf(pagespdf5);
  cpdf_deletePdf(pagespdf6);
  cpdf_deletePdf(pagespdf7);
  cpdf_deletePdf(pagespdf8);
  cpdf_deletePdf(pagespdf9);
  cpdf_deletePdf(pagespdf10);
  cpdf_deletePdf(pagespdf11);
  cpdf_deletePdf(pagespdf12);
  cpdf_deletePdf(pagespdf13);
  cpdf_deletePdf(pagespdf14);
  cpdf_deletePdf(pagespdf15);
  cpdf_deletePdf(pagespdf16);
  cpdf_deletePdf(pagespdf17);
  cpdf_deletePdf(pagespdf18);
  cpdf_deletePdf(pagespdf19);
  cpdf_deleteRange(r3);

  /* CHAPTER 4. Encryption */
  /* Encryption covered under Chapter 1 in cpdflib. */

  /* CHAPTER 5. Compression */
  printf("***** CHAPTER 5. Compression\n");
  int tocompress = cpdf_fromFile("cpdflibmanual.pdf", "");
  printf("---cpdf_compress()\n");
  cpdf_compress(tocompress);
  prerr();
  cpdf_toFile(tocompress, "testoutputs/05compressed.pdf", false, false);
  printf("---cpdf_decompress()\n");
  cpdf_decompress(tocompress);
  prerr();
  cpdf_toFile(tocompress, "testoutputs/05decompressed.pdf", false, false);
  printf("---cpdf_squeezeInMemory()\n");
  cpdf_squeezeInMemory(tocompress);
  cpdf_toFile(tocompress, "testoutputs/05squeezedinmemory.pdf", false, false);
  prerr();
  cpdf_deletePdf(tocompress);

  /* CHAPTER 6. Bookmarks */
  printf("***** CHAPTER 6. Bookmarks\n");
  int markspdf = cpdf_fromFile("cpdflibmanual.pdf", "");
  printf("---cpdf: get bookmarks\n");
  cpdf_startGetBookmarkInfo(markspdf);
  int n_marks = cpdf_numberBookmarks();
  prerr();
  printf("There are %i bookmarks\n", n_marks);
  for (int x = 0; x < n_marks; x++) {
    int level = cpdf_getBookmarkLevel(x);
    int page = cpdf_getBookmarkPage(markspdf, x);
    char *text = cpdf_getBookmarkText(x);
    int open = cpdf_getBookmarkOpenStatus(x);
    printf(
        "Bookmark at level %i points to page %i and has text \"%s\" and open "
        "%i\n",
        level, page, text, open);
  }
  prerr();
  cpdf_endGetBookmarkInfo();
  prerr();
  printf("---cpdf: set bookmarks\n");
  cpdf_startSetBookmarkInfo(1);
  prerr();
  cpdf_setBookmarkLevel(0, 0);
  cpdf_setBookmarkPage(markspdf, 0, 20);
  cpdf_setBookmarkOpenStatus(0, true);
  cpdf_setBookmarkText(0, "New bookmark!");
  prerr();
  cpdf_endSetBookmarkInfo(markspdf);
  prerr();
  cpdf_toFile(markspdf, "testoutputs/06newmarks.pdf", false, false);
  prerr();
  cpdf_deletePdf(markspdf);
  printf("---cpdf_getBookmarksJSON()\n");
  int marksjson = cpdf_fromFile("cpdflibmanual.pdf", "");
  int markslength;
  void *marksdata = cpdf_getBookmarksJSON(marksjson, &markslength);
  printf("Contains %i bytes of data\n", markslength);
  printf("---cpdf_setBookmarksJSON()\n");
  cpdf_setBookmarksJSON(marksjson, marksdata, markslength);
  cpdf_toFile(marksjson, "testoutputs/06jsonmarks.pdf", false, false);
  printf("---cpdf_tableOfContents()\n");
  int tocfile = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_tableOfContents(tocfile, cpdf_timesRoman, 12.0, "Table of Contents",
                       false);
  cpdf_toFile(tocfile, "testoutputs/06toc.pdf", false, false);
  cpdf_deletePdf(tocfile);

  /* CHAPTER 7. Presentations */
  /* Not included in the library version */

  /* CHAPTER 8. Logos, Watermarks and Stamps */
  printf("***** CHAPTER 8. Logos, Watermarks and Stamps\n");
  struct cpdf_position textpos = {
      .cpdf_anchor = cpdf_topLeft, .cpdf_coord1 = 20, .cpdf_coord2 = 20};
  int textfile = cpdf_fromFile("cpdflibmanual.pdf", "");
  int textfile_all = cpdf_all(textfile);
  printf("---cpdf_addText()\n");
  cpdf_addText(false,                  /* Just get metrics, don't add text */
               textfile,               /* pdf */
               textfile_all,           /* range */
               "Some Text~~~~~~~~~~!", /* text */
               textpos,                /* position */
               1.0,                    /* line spacing */
               1,                      /* starting bates number */
               cpdf_timesRoman,        /* font */
               20,                     /* font size */
               0.5,                    /* r */
               0.5,                    /* g */
               0.5,                    /* b */
               false,                  /* underneath */
               false,                  /* relative to crop box */
               true,                   /* outline text */
               0.5,                    /* opacity */
               cpdf_leftJustify,       /* justification */
               false,                  /* midline */
               false,                  /* topline */
               "",                     /* filename */
               1.0,                    /* line width */
               false);                 /* embed fonts */
  prerr();
  printf("---cpdf_addTextSimple()\n");
  cpdf_addTextSimple(textfile, textfile_all, "The text!", textpos,
                     cpdf_timesRoman, 50.0);
  prerr();
  cpdf_toFile(textfile, "testoutputs/08added_text.pdf", false, false);
  printf("---cpdf_removeText()\n");
  cpdf_removeText(textfile, textfile_all);
  cpdf_toFile(textfile, "testoutputs/08removed_text.pdf", false, false);
  prerr();
  printf("---cpdf_textWidth()\n");
  int width = cpdf_textWidth(cpdf_timesRoman, "What is the width of this?");
  int stamp = cpdf_fromFile("logo.pdf", "");
  int stampee = cpdf_fromFile("cpdflibmanual.pdf", "");
  int stamp_range = cpdf_all(stamp);
  printf("---cpdf_stampOn()\n");
  cpdf_stampOn(stamp, stampee, stamp_range);
  prerr();
  printf("---cpdf_stampUnder()\n");
  cpdf_stampUnder(stamp, stampee, stamp_range);
  prerr();
  struct cpdf_position pos = {
      .cpdf_anchor = cpdf_topLeft, .cpdf_coord1 = 20, .cpdf_coord2 = 20};
  printf("---cpdf_stampExtended()\n");
  cpdf_stampExtended(stamp, stampee, stamp_range, true, true, pos, true);
  prerr();
  cpdf_toFile(stamp, "testoutputs/08stamp_after.pdf", false, false);
  cpdf_toFile(stampee, "testoutputs/08stampee_after.pdf", false, false);
  int c1 = cpdf_fromFile("logo.pdf", "");
  int c2 = cpdf_fromFile("cpdflibmanual.pdf", "");
  printf("---cpdf_combinePages()\n");
  int c3 = cpdf_combinePages(c1, c2);
  cpdf_toFile(c3, "testoutputs/08c3after.pdf", false, false);
  cpdf_deletePdf(stamp);
  cpdf_deletePdf(stampee);
  cpdf_deletePdf(c1);
  cpdf_deletePdf(c2);
  cpdf_deletePdf(c3);
  cpdf_deletePdf(textfile);
  cpdf_deleteRange(stamp_range);
  cpdf_deleteRange(textfile_all);

  int undoc = cpdf_fromFile("cpdflibmanual.pdf", "");
  int logo = cpdf_fromFile("logo.pdf", "");
  int r_undoc = cpdf_all(undoc);
  printf("---cpdf_stampAsXObject()\n");
  char *name = cpdf_stampAsXObject(undoc, r_undoc, logo);
  prerr();
  char content[200];
  sprintf(content,
          "q 1 0 0 1 100 100 cm %s Do Q q 1 0 0 1 300 300 cm %s Do Q q 1 0 0 1 "
          "500 500 cm %s Do Q",
          name, name, name);
  printf("---cpdf_addContent()\n");
  cpdf_addContent(content, true, undoc, r_undoc);
  prerr();
  cpdf_toFile(undoc, "testoutputs/08demo.pdf", false, false);
  cpdf_deletePdf(undoc);
  cpdf_deletePdf(logo);
  cpdf_deleteRange(r_undoc);

  /* CHAPTER 9. Multipage facilities */
  printf("***** CHAPTER 9. Multipage facilities\n");
  int mp = cpdf_fromFile("cpdflibmanual.pdf", "");
  printf("---cpdf_twoUp()\n");
  cpdf_twoUp(mp);
  prerr();
  cpdf_toFile(mp, "testoutputs/09mp.pdf", false, false);
  printf("---cpdf_twoUpStack()\n");
  int mp2 = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_twoUpStack(mp2);
  prerr();
  cpdf_toFile(mp2, "testoutputs/09mp2.pdf", false, false);
  printf("---cpdf_impose()\n");
  int mp25 = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_impose(mp25, 5.0, 4.0, false, false, false, false, false, 40.0, 20.0,
              2.0);
  prerr();
  cpdf_toFile(mp25, "testoutputs/09mp25.pdf", false, false);
  int mp26 = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_impose(mp26, 2000, 1000, true, false, false, false, false, 40.0, 20.0,
              2.0);
  prerr();
  cpdf_toFile(mp26, "testoutputs/09mp26.pdf", false, false);
  printf("---cpdf_padBefore()\n");
  int r = cpdf_range(1, 10);
  int mp3 = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_padBefore(mp3, r);
  prerr();
  cpdf_toFile(mp3, "testoutputs/09mp3.pdf", false, false);
  printf("---cpdf_padAfter()\n");
  int mp4 = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_padAfter(mp4, r);
  prerr();
  cpdf_toFile(mp4, "testoutputs/09mp4.pdf", false, false);
  printf("---cpdf_padEvery()\n");
  int mp5 = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_padEvery(mp5, 5);
  prerr();
  cpdf_toFile(mp5, "testoutputs/09mp5.pdf", false, false);
  printf("---cpdf_padMultiple()\n");
  int mp6 = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_padMultiple(mp6, 10);
  prerr();
  cpdf_toFile(mp6, "testoutputs/09mp6.pdf", false, false);
  printf("---cpdf_padMultipleBefore()\n");
  int mp7 = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_padMultipleBefore(mp7, 23);
  prerr();
  cpdf_toFile(mp7, "testoutputs/09mp7.pdf", false, false);
  cpdf_deletePdf(mp);
  cpdf_deletePdf(mp2);
  cpdf_deletePdf(mp3);
  cpdf_deletePdf(mp4);
  cpdf_deletePdf(mp5);
  cpdf_deletePdf(mp6);
  cpdf_deletePdf(mp7);
  cpdf_deletePdf(mp25);
  cpdf_deletePdf(mp26);
  cpdf_deleteRange(r);

  /* CHAPTER 10. Annotations */
  printf("***** CHAPTER 10. Annotations\n");
  int annot = cpdf_fromFile("cpdflibmanual.pdf", "");
  int annotlength;
  printf("---cpdf_annotationsJSON()\n");
  void *data = cpdf_annotationsJSON(annot, &annotlength);
  printf("Contains %i bytes of data\n", annotlength);
  cpdf_deletePdf(annot);

  /* CHAPTER 11. Document Information and Metadata */
  printf("***** CHAPTER 11. Document Information and Metadata\n");
  int info = cpdf_fromFile("cpdflibmanual.pdf", "");
  int r_info = cpdf_all(info);
  printf("---cpdf_getVersion()\n");
  printf("minor version:%i\n", cpdf_getVersion(info));
  prerr();
  printf("---cpdf_getMajorVersion()\n");
  printf("major version:%i\n", cpdf_getMajorVersion(info));
  prerr();
  printf("---cpdf_getTitle()\n");
  char *title = cpdf_getTitle(info);
  printf("title: %s\n", title);
  printf("---cpdf_getAuthor()\n");
  char *author = cpdf_getAuthor(info);
  printf("author: %s\n", author);
  printf("---cpdf_getSubject()\n");
  char *subject = cpdf_getSubject(info);
  printf("subject: %s\n", subject);
  printf("---cpdf_getKeywords()\n");
  char *keywords = cpdf_getKeywords(info);
  printf("keywords: %s\n", keywords);
  printf("---cpdf_getCreator()\n");
  char *creator = cpdf_getCreator(info);
  printf("creator: %s\n", creator);
  printf("---cpdf_getProducer()\n");
  char *producer = cpdf_getProducer(info);
  printf("producer: %s\n", producer);
  printf("---cpdf_getCreationDate()\n");
  char *creationdate = cpdf_getCreationDate(info);
  printf("creationdate: %s\n", creationdate);
  printf("---cpdf_getModificationDate()\n");
  char *modificationdate = cpdf_getModificationDate(info);
  printf("modificationdate: %s\n", modificationdate);
  printf("---cpdf_getTitleXMP()\n");
  char *titleXMP = cpdf_getTitleXMP(info);
  printf("titleXMP: %s\n", titleXMP);
  printf("---cpdf_getAuthorXMP()\n");
  char *authorXMP = cpdf_getAuthorXMP(info);
  printf("authorXMP: %s\n", authorXMP);
  printf("---cpdf_getSubjectXMP()\n");
  char *subjectXMP = cpdf_getSubjectXMP(info);
  printf("subjectXMP: %s\n", subjectXMP);
  printf("---cpdf_getKeywordsXMP()\n");
  char *keywordsXMP = cpdf_getKeywordsXMP(info);
  printf("keywordsXMP: %s\n", keywordsXMP);
  printf("---cpdf_getCreatorXMP()\n");
  char *creatorXMP = cpdf_getCreatorXMP(info);
  printf("creatorXMP: %s\n", creatorXMP);
  printf("---cpdf_getProducerXMP()\n");
  char *producerXMP = cpdf_getProducerXMP(info);
  printf("producerXMP: %s\n", producerXMP);
  printf("---cpdf_getCreationDateXMP()\n");
  char *creationdateXMP = cpdf_getCreationDateXMP(info);
  printf("creationdateXMP: %s\n", creationdateXMP);
  printf("---cpdf_getModificationDateXMP()\n");
  char *modificationdateXMP = cpdf_getModificationDateXMP(info);
  printf("modificationdateXMP: %s\n", modificationdateXMP);
  prerr();
  printf("---cpdf_setTitle()\n");
  cpdf_setTitle(info, "title");
  prerr();
  printf("---cpdf_setAuthor()\n");
  cpdf_setAuthor(info, "author");
  prerr();
  printf("---cpdf_setSubject()\n");
  cpdf_setSubject(info, "subject");
  prerr();
  printf("---cpdf_setKeywords()\n");
  cpdf_setKeywords(info, "keywords");
  prerr();
  printf("---cpdf_setCreator()\n");
  cpdf_setCreator(info, "creator");
  prerr();
  printf("---cpdf_setProducer()\n");
  cpdf_setProducer(info, "producer");
  prerr();
  printf("---cpdf_setCreationDate()\n");
  cpdf_setCreationDate(info, "now");
  prerr();
  printf("---cpdf_setModificationDate()\n");
  cpdf_setModificationDate(info, "now");
  prerr();
  printf("---cpdf_setTitleXMP()\n");
  cpdf_setTitleXMP(info, "title");
  prerr();
  printf("---cpdf_setAuthorXMP()\n");
  cpdf_setAuthorXMP(info, "author");
  prerr();
  printf("---cpdf_setSubjectXMP()\n");
  cpdf_setSubjectXMP(info, "subject");
  prerr();
  printf("---cpdf_setKeywordsXMP()\n");
  cpdf_setKeywordsXMP(info, "keywords");
  prerr();
  printf("---cpdf_setCreatorXMP()\n");
  cpdf_setCreatorXMP(info, "creator");
  prerr();
  printf("---cpdf_setProducerXMP()\n");
  cpdf_setProducerXMP(info, "producer");
  prerr();
  printf("---cpdf_setCreationDateXMP()\n");
  cpdf_setCreationDateXMP(info, "now");
  prerr();
  printf("---cpdf_setModificationDateXMP()\n");
  cpdf_setModificationDateXMP(info, "now");
  prerr();
  cpdf_toFile(info, "testoutputs/11setinfo.pdf", false, false);
  printf("---cpdf_getDateComponents()\n");
  int year, month, day, hour, minute, second, hour_offset, minute_offset;
  cpdf_getDateComponents("D:20061108125017Z", &year, &month, &day, &hour,
                         &minute, &second, &hour_offset, &minute_offset);
  prerr();
  printf("D:20061108125017Z = %i, %i, %i, %i, %i, %i, %i, %i\n", year, month,
         day, hour, minute, second, hour_offset, minute_offset);
  printf("---cpdf_dateStringOfComponents()\n");
  char *datestring = cpdf_dateStringOfComponents(
      year, month, day, hour, minute, second, hour_offset, minute_offset);
  printf("%s\n", datestring);
  printf("---cpdf_getPageRotation()\n");
  int rotation = cpdf_getPageRotation(info, 1);
  prerr();
  printf("/Rotate on page 1 = %i\n", rotation);
  printf("---cpdf_hasBox()\n");
  int hasbox = cpdf_hasBox(info, 1, "/CropBox");
  prerr();
  printf("hasbox: %i\n", hasbox);
  double minx, maxx, miny, maxy;
  printf("---cpdf_getMediaBox()\n");
  cpdf_getMediaBox(info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf("Media: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("---cpdf_getCropBox()\n");
  cpdf_getCropBox(info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf("Crop: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("---cpdf_getBleedBox()\n");
  cpdf_getBleedBox(info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf("Bleed: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("---cpdf_getArtBox()\n");
  cpdf_getArtBox(info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf("Art: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("---cpdf_getTrimBox()\n");
  cpdf_getTrimBox(info, 1, &minx, &maxx, &miny, &maxy);
  prerr();
  printf("Trim: %f %f %f %f\n", minx, maxx, miny, maxy);
  printf("---cpdf_setMediaBox()\n");
  cpdf_setMediabox(info, r_info, 100, 500, 150, 550);
  prerr();
  printf("---cpdf_setCropBox()\n");
  cpdf_setCropBox(info, r_info, 100, 500, 150, 550);
  prerr();
  printf("---cpdf_setTrimBox()\n");
  cpdf_setTrimBox(info, r_info, 100, 500, 150, 550);
  prerr();
  printf("---cpdf_setArtBox()\n");
  cpdf_setArtBox(info, r_info, 100, 500, 150, 550);
  prerr();
  printf("---cpdf_setBleedBox()\n");
  cpdf_setBleedBox(info, r_info, 100, 500, 150, 550);
  prerr();
  cpdf_toFile(info, "testoutputs/11setboxes.pdf", false, false);
  printf("---cpdf_markTrapped()\n");
  cpdf_markTrapped(info);
  prerr();
  printf("---cpdf_markTrappedXMP()\n");
  cpdf_markTrappedXMP(info);
  prerr();
  cpdf_toFile(info, "testoutputs/11trapped.pdf", false, false);
  printf("---cpdf_markUntrapped()\n");
  cpdf_markUntrapped(info);
  prerr();
  printf("---cpdf_markUntrappedXMP()\n");
  cpdf_markUntrappedXMP(info);
  prerr();
  cpdf_toFile(info, "testoutputs/11untrapped.pdf", false, false);
  printf("---cpdf_setPageLayout()\n");
  cpdf_setPageLayout(info, cpdf_twoColumnLeft);
  prerr();
  printf("---cpdf_setPageMode()\n");
  cpdf_setPageMode(info, cpdf_useOutlines);
  prerr();
  printf("---cpdf_hideToolbar()\n");
  cpdf_hideToolbar(info, true);
  prerr();
  printf("---cpdf_hideMenubar()\n");
  cpdf_hideMenubar(info, true);
  prerr();
  printf("---cpdf_hideWindowUi()\n");
  cpdf_hideWindowUi(info, true);
  prerr();
  printf("---cpdf_fitWindow()\n");
  cpdf_fitWindow(info, true);
  prerr();
  printf("---cpdf_centerWindow()\n");
  cpdf_centerWindow(info, true);
  prerr();
  printf("---cpdf_displayDocTitle()\n");
  cpdf_displayDocTitle(info, true);
  prerr();
  printf("---cpdf_openAtPage()\n");
  cpdf_openAtPage(info, true, 4);
  prerr();
  cpdf_toFile(info, "testoutputs/11open.pdf", false, false);
  printf("---cpdf_setMetadataFromFile()\n");
  cpdf_setMetadataFromFile(info, "cpdflibmanual.pdf");
  prerr();
  cpdf_toFile(info, "testoutputs/11metadata1.pdf", false, false);
  printf("---cpdf_setMetadataFromByteArray()\n");
  cpdf_setMetadataFromByteArray(info, "BYTEARRAY", 9);
  prerr();
  cpdf_toFile(info, "testoutputs/11metadata2.pdf", false, false);
  int metadata_length;
  printf("---cpdf_getMetadata()\n");
  void *metadata;
  metadata = cpdf_getMetadata(info, &metadata_length);
  prerr();
  printf("---cpdf_removeMetadata()\n");
  cpdf_removeMetadata(info);
  prerr();
  printf("---cpdf_createMetadata()\n");
  cpdf_createMetadata(info);
  prerr();
  cpdf_toFile(info, "testoutputs/11metadata3.pdf", false, false);
  printf("---cpdf_setMetadataDate()\n");
  cpdf_setMetadataDate(info, "now");
  prerr();
  cpdf_toFile(info, "testoutputs/11metadata4.pdf", false, false);
  printf("---cpdf_addPageLabels()\n");
  cpdf_addPageLabels(info, cpdf_uppercaseRoman, "PREFIX-", 1, r_info, false);
  prerr();
  printf("---cpdf: get page labels\n");
  int pln = cpdf_startGetPageLabels(info);
  printf("There are %i labels\n", pln);
  prerr();
  int pl1 = cpdf_getPageLabelStyle(0);
  prerr();
  char *pl2 = cpdf_getPageLabelPrefix(0);
  prerr();
  int pl3 = cpdf_getPageLabelOffset(0);
  prerr();
  int pl4 = cpdf_getPageLabelRange(0);
  prerr();
  printf("Page label: %i, %s, %i, %i\n", pl1, pl2, pl3, pl4);
  cpdf_endGetPageLabels();
  prerr();
  printf("---cpdf_removePageLabels()\n");
  cpdf_removePageLabels(info);
  prerr();
  cpdf_toFile(info, "testoutputs/11pagelabels.pdf", false, false);
  printf("---cpdf_getPageLabelStringForPage()\n");
  char *pllabel = cpdf_getPageLabelStringForPage(info, 1);
  prerr();
  printf("Label string is %s\n", pllabel);
  cpdf_deletePdf(info);
  cpdf_deleteRange(r_info);

  /* CHAPTER 12. File Attachments */
  printf("***** CHAPTER 12. File Attachments\n");
  int attachments = cpdf_fromFile("testinputs/has_attachments.pdf", "");
  printf("---cpdf_attachFile()\n");
  cpdf_attachFile("testinputs/image.pdf", attachments);
  prerr();
  printf("---cpdf_attachFileToPage()\n");
  cpdf_attachFileToPage("testinputs/image.pdf", attachments, 1);
  prerr();
  printf("---cpdf_attachFileFromMemory()\n");
  cpdf_attachFileFromMemory((void *)0, 0, "metadata.txt", attachments);
  prerr();
  printf("---cpdf_attachFileToPageFromMemory()\n");
  cpdf_attachFileToPageFromMemory((void *)0, 0, "metadata.txt", attachments, 1);
  prerr();
  cpdf_toFile(attachments, "testoutputs/12with_attachments.pdf", false, false);
  printf("---cpdf: get attachments\n");
  cpdf_startGetAttachments(attachments);
  prerr();
  int numatt = cpdf_numberGetAttachments();
  prerr();
  printf("There are %i attachments to get\n", numatt);
  for (int x = 0; x < numatt; x++) {
    printf("Attachment %i is named %s\n", x, cpdf_getAttachmentName(x));
    printf("It is on page %i\n", cpdf_getAttachmentPage(x));
    int length;
    cpdf_getAttachmentData(x, &length);
    printf("Contains %i bytes of data\n", length);
  };
  prerr();
  cpdf_endGetAttachments();
  prerr();
  printf("---cpdf_removeAttachedFiles()\n");
  cpdf_removeAttachedFiles(attachments);
  prerr();
  cpdf_toFile(attachments, "testoutputs/12removed_attachments.pdf", false,
              false);
  cpdf_deletePdf(attachments);

  /* CHAPTER 13. Images */
  printf("***** CHAPTER 13. Images\n");
  printf("---cpdf: get image resolution\n");
  int images = cpdf_fromFile("testinputs/image.pdf", "");
  int n = cpdf_startGetImageResolution(images, 500000.);
  prerr();
  for (int x = 0; x < n; x++) {
    int page = cpdf_getImageResolutionPageNumber(x);
    char *name = cpdf_getImageResolutionImageName(x);
    int xp = cpdf_getImageResolutionXPixels(x);
    int yp = cpdf_getImageResolutionYPixels(x);
    double xres = cpdf_getImageResolutionXRes(x);
    double yres = cpdf_getImageResolutionYRes(x);
    printf("IMAGE: %i, %s, %i, %i, %f, %f\n", page, name, xp, yp, xres, yres);
  }
  prerr();
  cpdf_endGetImageResolution();
  prerr();
  cpdf_deletePdf(images);

  /* CHAPTER 14. Fonts */
  printf("***** CHAPTER 14. Fonts\n");
  int fonts = cpdf_fromFile("cpdflibmanual.pdf", "");
  int fonts2 = cpdf_fromFile("testinputs/frontmatter.pdf", "");
  printf("---cpdf: Get Fonts\n");
  cpdf_startGetFontInfo(fonts);
  prerr();
  int n_fonts = cpdf_numberFonts();
  prerr();
  for (int x = 0; x < n_fonts; x++) {
    printf("Page %i, font %s has type %s and encoding %s\n",
           cpdf_getFontPage(x), cpdf_getFontName(x), cpdf_getFontType(x),
           cpdf_getFontEncoding(x));
  };
  prerr();
  cpdf_endGetFontInfo();
  prerr();
  printf("---cpdf_removeFonts()\n");
  int fontrange = cpdf_all(fonts);
  cpdf_removeFonts(fonts);
  prerr();
  cpdf_toFile(fonts, "testoutputs/14remove_fonts.pdf", false, false);
  printf("---cpdf_copyFont()\n");
  cpdf_copyFont(fonts, fonts2, fontrange, 1, "/F0");
  prerr();
  cpdf_deletePdf(fonts);
  cpdf_deletePdf(fonts2);
  cpdf_deleteRange(fontrange);

  /* CHAPTER 15. PDF and JSON */
  printf("***** CHAPTER 15. PDF and JSON\n");
  printf("---cpdf_outputJSON()\n");
  int json = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_outputJSON("testoutputs/15json.json", false, false, false, json);
  prerr();
  cpdf_outputJSON("testoutputs/15jsonnostream.json", false, true, false, json);
  prerr();
  cpdf_outputJSON("testoutputs/15jsonparsed.json", true, false, false, json);
  prerr();
  cpdf_outputJSON("testoutputs/15jsondecomp.json", false, false, true, json);
  prerr();
  printf("---cpdf_fromJSON()\n");
  int jsonpdf = cpdf_fromJSON("testoutputs/15jsonparsed.json");
  prerr();
  cpdf_toFile(jsonpdf, "testoutputs/15fromjson.pdf", false, false);
  int jbuflen;
  printf("---cpdf_outputJSONMemory()\n");
  void *jbuf = cpdf_outputJSONMemory(jsonpdf, false, false, false, &jbuflen);
  printf("---cpdf_fromJSONMemory()\n");
  int jfrommem = cpdf_fromJSONMemory(jbuf, jbuflen);
  cpdf_toFile(jfrommem, "testoutputs/15fromJSONMemory.pdf", false, false);
  prerr();
  cpdf_deletePdf(json);
  cpdf_deletePdf(jsonpdf);

  /* CHAPTER 16. Optional Content Groups */
  int ocg = cpdf_fromFile("testinputs/has_ocgs.pdf", "");
  printf("***** CHAPTER 16. Optional Content Groups\n");
  printf("---cpdf: Get OCG List\n");
  int nocgs = cpdf_startGetOCGList(ocg);
  prerr();
  printf("%s", cpdf_OCGListEntry(0));
  printf("\n");
  prerr();
  cpdf_endGetOCGList();
  prerr();
  printf("---cpdf_OCGCoalesce()\n");
  cpdf_OCGCoalesce(ocg);
  prerr();
  printf("---cpdf_OCGRename()\n");
  cpdf_OCGRename(ocg, "Layer 1", "Layer 2");
  prerr();
  printf("---cpdf_OCGOrderAll()\n");
  cpdf_OCGOrderAll(ocg);
  prerr();
  cpdf_deletePdf(ocg);

  /* CHAPTER 17. Creating New PDFs */
  printf("***** CHAPTER 17. Creating New PDFs\n");
  printf("---cpdf_blankDocument()\n");
  int blankdoc = cpdf_blankDocument(100.0, 200.0, 20);
  prerr();
  cpdf_toFile(blankdoc, "testoutputs/01blank.pdf", false, false);
  printf("---cpdf_blankDocumentPaper()\n");
  int blanksized = cpdf_blankDocumentPaper(cpdf_a4portrait, 10);
  prerr();
  cpdf_toFile(blanksized, "testoutputs/01blanka4.pdf", false, false);
  printf("---cpdf_textToPDF()\n");
  int ttpdf =
      cpdf_textToPDF(500.0, 600.0, cpdf_timesItalic, 8.0, "cpdflibtest.c");
  cpdf_toFile(ttpdf, "testoutputs/01ttpdf.pdf", false, false);
  printf("---cpdf_textToPDFPaper()\n");
  int ttpdfpaper = cpdf_textToPDFPaper(cpdf_a4portrait, cpdf_timesBoldItalic,
                                       10.0, "cpdflibtest.c");
  cpdf_toFile(ttpdfpaper, "testoutputs/01ttpdfpaper.pdf", false, false);
  cpdf_deletePdf(ttpdf);
  cpdf_deletePdf(ttpdfpaper);
  cpdf_deletePdf(blankdoc);
  cpdf_deletePdf(blanksized);

  /* CHAPTER 18. Miscellaneous */
  printf("***** CHAPTER 18. Miscellaneous\n");
  int misc = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc2 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc3 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc4 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc5 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc6 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc7 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc8 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc9 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc10 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc11 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc12 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misclogo = cpdf_fromFile("logo.pdf", "");
  int misc_r = cpdf_all(misc);
  printf("---cpdf_draft()\n");
  cpdf_draft(misc, misc_r, true);
  prerr();
  cpdf_toFile(misc, "testoutputs/17draft.pdf", false, false);
  printf("---cpdf_removeAllText()\n");
  cpdf_removeAllText(misc2, misc_r);
  prerr();
  cpdf_toFile(misc2, "testoutputs/17removealltext.pdf", false, false);
  printf("---cpdf_blackText()\n");
  cpdf_blackText(misc3, misc_r);
  prerr();
  cpdf_toFile(misc3, "testoutputs/17blacktext.pdf", false, false);
  printf("---cpdf_blackLines()\n");
  cpdf_blackLines(misc4, misc_r);
  prerr();
  cpdf_toFile(misc4, "testoutputs/17blacklines.pdf", false, false);
  printf("---cpdf_blackFills()\n");
  cpdf_blackFills(misc5, misc_r);
  prerr();
  cpdf_toFile(misc5, "testoutputs/17blackfills.pdf", false, false);
  printf("---cpdf_thinLines()\n");
  cpdf_thinLines(misc6, misc_r, 2.0);
  prerr();
  cpdf_toFile(misc6, "testoutputs/17thinlines.pdf", false, false);
  printf("---cpdf_copyId()\n");
  cpdf_copyId(misclogo, misc7);
  prerr();
  cpdf_toFile(misc7, "testoutputs/17copyid.pdf", false, false);
  printf("---cpdf_removeId()\n");
  cpdf_removeId(misc8);
  prerr();
  cpdf_toFile(misc8, "testoutputs/17removeid.pdf", false, false);
  printf("---cpdf_setVersion()\n");
  cpdf_setVersion(misc9, 1);
  prerr();
  cpdf_toFile(misc9, "testoutputs/17setversion.pdf", false, false);
  printf("---cpdf_setFullVersion()\n");
  cpdf_setFullVersion(misc10, 2, 0);
  prerr();
  cpdf_toFile(misc10, "testoutputs/17setfullversion.pdf", false, false);
  printf("---cpdf_removeDictEntry()\n");
  int misc13 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc14 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc15 = cpdf_fromFile("cpdflibmanual.pdf", "");
  int misc16 = cpdf_fromFile("cpdflibmanual.pdf", "");
  cpdf_removeDictEntry(misc11, "/Producer");
  prerr();
  cpdf_toFile(misc11, "testoutputs/17removedictentry.pdf", false, false);
  printf("---cpdf_removeDictEntrySearch()\n");
  cpdf_removeDictEntrySearch(misc13, "/Producer", "1");
  prerr();
  cpdf_toFile(misc13, "testoutputs/17removedictentrysearch.pdf", false, false);
  printf("---cpdf_replaceDictEntry()\n");
  cpdf_replaceDictEntry(misc14, "/Producer", "\"NewProducer\"");
  prerr();
  cpdf_toFile(misc14, "testoutputs/17replacedictentry.pdf", false, false);
  printf("---cpdf_replaceDictEntrySearch()\n");
  cpdf_replaceDictEntrySearch(misc15, "/Producer", "\"NewProducer2\"",
                              "\"pdfTeX-1.40.22\"");
  prerr();
  cpdf_toFile(misc15, "testoutputs/17replacedictentrysearch.pdf", false, false);
  printf("---cpdf_getDictEntries()\n");
  int gedlength;
  void *geddata = cpdf_getDictEntries(misc16, "/Producer", &gedlength);
  printf("length of entries data = %i\n", gedlength);
  prerr();
  printf("---cpdf_removeClipping()\n");
  cpdf_removeClipping(misc12, misc_r);
  prerr();
  cpdf_toFile(misc12, "testoutputs/17removeclipping.pdf", false, false);
  cpdf_deletePdf(misc);
  cpdf_deletePdf(misc2);
  cpdf_deletePdf(misc3);
  cpdf_deletePdf(misc4);
  cpdf_deletePdf(misc5);
  cpdf_deletePdf(misc6);
  cpdf_deletePdf(misc7);
  cpdf_deletePdf(misc8);
  cpdf_deletePdf(misc9);
  cpdf_deletePdf(misc10);
  cpdf_deletePdf(misc11);
  cpdf_deletePdf(misc12);
  cpdf_deletePdf(misc13);
  cpdf_deletePdf(misc14);
  cpdf_deletePdf(misc15);
  cpdf_deletePdf(misc16);
  cpdf_deletePdf(misclogo);
  cpdf_deleteRange(misc_r);

  /* cpdf_onExit(); */
  return 0;
}
