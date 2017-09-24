curl --silent 'http://aqicn.org/?city=Shanghai&widgetscript&size=large' \
| sed ':t;N;s/\n//;b t' \
| sed 's/\([^\n]\+\)\\\">/AQ: /g' \
| sed "s/<\/div>\([^\n]\+\)10px;'>/ Temp: /g" \
| sed 's/<\/td>\([^\n]\+\)//g' \
&& echo -e '\u00B0C'
