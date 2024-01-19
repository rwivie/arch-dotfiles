#!/bin/sh

# Set your location inside the /etc/environment file using WTRLOC variable
# Ex.: WTRLOC=Argentina  WTRLOC=Coleman

# Get the weather
# %C is a weather type, %t is a temperature
wtr=$(curl -s https://wttr.in/"$WTRLOC"?format="%C/%t\n")

# Split the taken data between two variables
wtrtype=$(echo "$wtr" | cut -d "/" -f1)
wtrtemp=$(echo "$wtr" | cut -d "/" -f2)

# Change the weather icon according to the time
curtime=$(date '+%H')

time_check() {
	if [ "$curtime" -ge 21 ] && [ "$curtime" -le 23 ] || [ "$curtime" -le 4 ];
	then
		# Nighttime icon
		wtricn="$1"
	else
		# Daytime icon
		wtricn="$2"
	fi
}

# Deside on the icon of the weather type
case $wtrtype in 
	"Sunny") 		  time_check '\uE233' '\uE234';;
	"Clear") 		  time_check '\uE233' '\uE234';;
	"Mist")                        wtricn='\uE235';;
	"Fog")                         wtricn='\uE235';;
	(*?fog)                        wtricn='\uE235';;
	"Partly cloudy")  time_check '\uE232' '\uE231';;
	"Cloudy")                      wtricn='\uE22B';;
	"Overcast")                    wtricn='\uE22B';;
	(*?rain*)                      wtricn='\uE230';;
	"Light drizzle")               wtricn='\uE230';;
	"Patchy light drizzle")        wtricn='\uE230';;
	"Thundery outbreaks possible") wtricn='\uE22C';;
	(*?sleet*)                     wtricn='\uE22E';;
	(*?snow*)                      wtricn='\uE22E';;
	(*?freezing*)                  wtricn='\uE22E';;
	"Unknown location;")           wtricn='x';;
	*)                             wtricn='x';;
esac

printf '%b%s\n' "$wtricn" "$wtrtemp"
