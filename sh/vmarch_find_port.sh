PID=$1
PORT=$(netstat -tlnp | awk '$7~/^'"$PID"'\/.*?$/ {print $4}')
echo "$PORT"