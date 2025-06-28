library(dplyr)


Mediciones = read.csv("~/Académico/2025/Ciclo 1/Estadística/Diseño de Experimentos/Tareas/Proyecto/Mediciones - Hoja 1.csv")

str(Mediciones)

# Se manipulan los datos
Mediciones$Tiempo..s. <- gsub(",", ".", Mediciones$Tiempo..s.)
Mediciones$Tiempo..s. <- as.numeric(Mediciones$Tiempo..s.)

Mediciones$Tamano = factor(Mediciones$Tamano)


# En primer lugar se obtienen

boxplot(Tiempo..ms.~Algoritmo, data = Mediciones)

boxplot(Tiempo..ms.~Tamano, data = Mediciones)

boxplot(Tiempo..s.~Algoritmo, data = Mediciones)

boxplot(Tiempo..s.~Algoritmo, data = Mediciones)

# Calculo de las media


medgen = mean(Mediciones$Tiempo..s.)

print(medgen)


# Promedios marginales de cada factor

marginal_algorit = tapply(Mediciones$Tiempo..s., Mediciones$Algoritmo, mean)
print(marginal_algorit)


marginal_tamano = tapply(Mediciones$Tiempo..s., Mediciones$Tamano, mean)

print(marginal_tamano)


# Se procede a calcular los efectos simples

alfa = marginal_algorit - medgen

beta = marginal_tamano - medgen

print(alfa)

print(beta)

# Se calcula los promedios observados

med = tapply(Mediciones$Tiempo..s., list(Mediciones$Tamano,Mediciones$Algoritmo), mean)

print(med)



# se tiene la hipótesis de interacción

library(ggplot2)

ggplot(Mediciones, aes(x = Tamano, y = Tiempo..s., group = Algoritmo, color = Algoritmo)) +
  stat_summary(fun = mean, geom = "line", aes(linetype = Algoritmo), size = 1.2) +
  labs(title = "Promedio de Tiempo por Tamaño y Algoritmo",
       x = "Tamaño del problema",
       y = "Tiempo (segundos)") +
  theme_minimal()

# Se calculan los efectos simples y de interacción

mod1 = aov(Tiempo..s.~Algoritmo*Tamano, data = Mediciones)
model.tables(mod1)

# Análisis de varianza

boxplot(Tiempo..s.~Algoritmo+Tamano, ylab = "Tiempo (segundos)",
        xlab = "Algoritmo:Tamano", data = Mediciones)

v = tapply(Mediciones$Tiempo..s., list(Mediciones$Tamano, Mediciones$Algoritmo), var)

print(round(v, 5))
# Se realiza el test de Barlett

bartlett.test(Tiempo..s. ~ interaction(Tamano, Algoritmo), data = Mediciones)


