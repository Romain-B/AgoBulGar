#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

if (length(args)==0) {
  stop("At least one argument must be supplied (input file).n", call.=FALSE)
} else if (length(args)==1) {
  # default output file
  args[2] = "out.pdf"
}

library("ggplot2")

data <- read.table(args[1], header = TRUE, sep = ";")

pdf(args[2])

obj <- ggplot(data =  data, aes(x = Ainit, y = T)) + 
      geom_tile(aes(fill = val)) +
      scale_fill_gradient(name="Etat final \n du système")

print(obj)
dev.off()
