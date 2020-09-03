# Redes de Computadores 
## Trabalho prático 1
O presente trabalho prático consiste em um jogo da forca estabelecido entre um servidor e diversos clientes (não simultâneos).

A palavra utilizada no jogo está escrita dentro do próprio código do servidor.

Para que os usuários do cliente adivinhem a palavra do jogo da forca, enviam mensagens com palpites para o servidor, que responderá sobre a ocorrência ou não da letra, e as posições onde ela ocorre em caso positivo.

O servidor comunica o encerramento do jogo quando todas as letras forem adivinhadas.

### Aluna
Gabriela Peres Neme   2018054745


### Compilar

```
make
```

### Rodar o servidor
```
./servidor <porta>
```

### Rodar cliente
```
./cliente <ip-servidor(IPv4/IPv6)> <porta-servidor>
```
