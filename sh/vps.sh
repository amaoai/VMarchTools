JAVA_PS=$(jps -l | grep -v "sun.tools.jps.Jps")

PID=
NAME=
MEM=
CPU=
OUT=

echo "$JAVA_PS" | while read line
do
  PID="$(echo "$line" | awk '{print $1}')"
  NAME="$(echo "$line" | awk '{print $2}')"

  AUX="$(ps aux | grep "$PID" | grep -v "grep")"
  CPU="$(echo "$AUX" | awk '{print $3}')"
  MEM="$(echo "$AUX" | awk '{print $4}')"

  OUT="$PID $NAME $CPU% $MEM%"
  echo "$OUT"

  PORT="$(netstat -antup | grep $PID | grep LISTEN | awk '{ print $1, substr($4, index($4, ":")) }')"
  # shellcheck disable=SC2001
  PORT="$(echo "$PORT" | sed 's/://g')"
  echo "$PORT" | while read xline
  do
    echo "  $xline"
  done
done
