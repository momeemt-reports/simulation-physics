#include "plots.h"

void output_jpeg (char *dest, char *input, int x0, int x1, int y0, int y1) {
  FILE *gnu_plot = popen("gnuplot", "w");
  fprintf(gnu_plot, "set terminal jpeg\n");
  {
    char command[120];
    sprintf(command, "set output \"out/%s.jpg\"\n", dest);
    fprintf(gnu_plot, "%s", command);
  }
  {
    char command[120];
    sprintf(command, "set xrange [%d:%d]\n", x0, x1);
    fprintf(gnu_plot, "%s", command);
  }
  {
    char command[120];
    sprintf(command, "set yrange [%d:%d]\n", y0, y1);
    fprintf(gnu_plot, "%s", command);
  }
  fprintf(gnu_plot, "set xlabel \"x\"\n");
  fprintf(gnu_plot, "set ylabel \"y\"\n");
  fprintf(gnu_plot, "set size ratio 1\n");
  fprintf(gnu_plot, "unset key\n");
  {
    char command[120];
    sprintf(command, "plot \"%s\"\n", input);
    fprintf(gnu_plot, "%s", command);
  }
  pclose(gnu_plot);
}

void output_gif (char *dest, char *input, int frame_num, int x0, int x1, int y0, int y1, int row_num) {
  FILE *gnu_plot = popen("gnuplot", "w");
  fprintf(gnu_plot, "set terminal gif animate delay 8 optimize\n");
  {
    char command[120];
    sprintf(command, "set output \"out/%s.gif\"\n", dest);
    fprintf(gnu_plot, "%s", command);
  }
  fprintf(gnu_plot, "set xlabel \"x\"\n");
  fprintf(gnu_plot, "set ylabel \"y\"\n");
  fprintf(gnu_plot, "set size ratio 1\n");
  fprintf(gnu_plot, "unset key\n");
  {
    char command[120];
    sprintf(command, "do for [i=0: %d] {\n", frame_num-1);
    fprintf(gnu_plot, "%s", command);
  }
  {
    char command[120];
    sprintf(
      command, "  plot [%d:%d][%d:%d] \"%s\" every ::i*%d+1::(i+1)*%d using 1:2\n",
      x0, x1, y0, y1, input, row_num, row_num
    );
    printf("%s", command);
    fprintf(gnu_plot, "%s", command);
  }
  fprintf(gnu_plot, "}\n");
  pclose(gnu_plot);
}