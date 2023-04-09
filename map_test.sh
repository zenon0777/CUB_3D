echo "Please run me like this ./maps/map_test.sh"
echo "Following maps should all fail and exit."
echo "If the tester gets stuck, that means something is not right and the program likely does not handle that case correctly."

mapio_failed=0
mapio_ok=0

function_check_error () {
	if [ "$?" -ne 1 ]; then
		printf "TEST FAIL: $1\n";
		((mapio_failed=maps_failed+1))
	else
		printf "TEST OK for map $1\n";
		((mapio_ok=maps_ok+1))
	fi
}

./cub ./mapio/double_identifier.cb > /dev/null 2>&1
function_check_error "Double ID"
./cub ./mapio/double_rgb.cub > /dev/null 2>&1
function_check_error "Double RGB"
./cub ./mapio/double_map.cub > /dev/null 2>&1
function_check_error "Double Map"
./cub ./mapio/emptymap.cub > /dev/null 2>&1
function_check_error "Empty map"
./cub ./mapio/invalid_symbol.cub > /dev/null 2>&1
function_check_error "invalid symbol in map"
./cub ./mapio/invalid_texture.cub > /dev/null 2>&1
function_check_error "invalid texture"
./cub ./mapio/multiple_player.cub > /dev/null 2>&1
function_check_error "double player"
./cub ./mapio/non_square_tex.cub > /dev/null 2>&1
function_check_error "non square texture"
./cub ./mapio/unknown_key.cub > /dev/null 2>&1
function_check_error "unknown direction key"
./cub ./mapio/wrong_rgb.cub > /dev/null 2>&1
function_check_error "overflow rgb value"
./cub ./mapio/wrong_rgb2.cub > /dev/null 2>&1
function_check_error "underflow rgb value"

FILES="./mapio/invalid_mapio/*"
for f in $FILES
do
  ./cub $f > /dev/null 2>&1

  function_check_error "$f"
done

echo "\n\nTesting of all mapio finished!"
echo "Result is:"
echo "Correctly handled mapio: $mapio_ok"
echo "NOT correctly handled mapio: $mapio_failed"
