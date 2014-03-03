# Протокол чата

Запрос: `nicname;command[;parameter]`.

Команды:

* `interlocutors` &mdash; запрос списка собеседников; параметра не имеет; в
ответ сервер вернёт список ников собеседников, разделённый символом
&laquo;;&raquo;;
* `message` &mdash; отправка сообщения; параметр &mdash; текст сообщений; в
ответ сервер вернёт строку &laquo;ok&raquo;;
* `history` &mdash; запрос истории сообщений; параметр &mdash; временная метка
(Unix time), с которой нужны сообщения; сервер вернёт список сообщений,
временная метка которых **больше** переданной в параметре; сообщения будут
разделённы символом &laquo;;&raquo;; каждое сообщение будет иметь формат
`nickname:timestamp:text`.

При ошибках сервер возвращает строку в формате `error;description`.