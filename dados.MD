# Dados dos Testes

- **Ambiente:** 8 computadores do LCI 12

---

# Execução Sequencial

| Execução | Real | User | Sys |
|-----------|------|------|-----|
| 1 | 19m49,701s | 19m48,385s | 0m0,379s |
| 2 | - | - | - |
| 3 | - | - | - |
| 4 | - | - | - |
| 5 | - | - | - |

---

# Execução Paralela — 2 Processos

| Execução | Real | User | Sys |
|-----------|------|------|-----|
| 1 | 10m44,358s  | 21m26,190s | 0m0,405s |
| 2 | 10m44,833s  | 21m26,963s | 0m0,389s |
| 3 | 10m40,978s  | 21m20,142s | 0m0,391s |
| 4 | 10m40,786s  | 21m19,909s | 0m0,267s |
| 5 | 10m41,004s  | 21m20,294s | 0m0,296s |

---

# Execução Paralela — 4 Processos

| Execução | Real | User | Sys |
|-----------|------|------|-----|
| 1 | 8m9,926s  | 26m54,259s | 0m1,028s |
| 2 | 8m19,771s | 27m23,442s | 0m2,212s |
| 3 | 7m11,895s | 24m45,723s | 0m2,159s |
| 4 | 7m12,437s | 24m51,019s | 0m2,133s |
| 5 | 7m12,011s | 24m52,258s | 0m2,061s |

---

# Execução Paralela — 8 Processos

| Execução | Real | User | Sys |
|-----------|------|------|-----|
| 1 | 3m30,460s | 10m53,872s | 1m48,227s |
| 2 | 3m30,900s | 11m4,504s  | 1m48,472s |
| 3 | 4m2,669s  | 12m4,831s  | 0m25,039s |
| 4 | 3m53,184s | 11m27,628s | 1m4,954s  |
| 5 | 4m0,040s  | 11m44,555s | 1m24,873s |

---

# Execução Paralela — 16 Processos

| Execução | Real | User | Sys |
|-----------|------|------|------|
| 1 | 1m59,411s | 5m26,558s | 1m41,734s |
| 2 | 2m01,263s | 5m26,871s | 1m45,810s |
| 3 | 2m01,307s | 5m28,970s | 1m44,887s |
| 4 | 2m01,525s | 5m24,548s | 1m43,705s |
| 5 | 1m59,684s | 5m23,308s | 1m41,215s |

---

# Execução Paralela — 32 Processos

| Execução | Real | User | Sys |
|-----------|------|------|------|
| 1 | 0m50,383s | 2m24,537s | 0m51,124s |
| 2 | 0m53,502s | 2m27,971s | 0m53,220s |
| 3 | 0m54,159s | 2m26,456s | 0m51,516s |
| 4 | 0m59,600s | 2m29,595s | 0m54,055s |
| 5 | 1m00,439s | 2m29,894s | 0m53,485s |

---

## Observações

- Ambiente de testes composto por **8 computadores do laboratório LCI 12**.
- Foram realizadas **5 execuções** para cada configuração.
- Campos não preenchidos indicam medições ainda não realizadas.