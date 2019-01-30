.name		"champ"
.comment	"petit champion"

l0: live %1
	live %1
	ld %57672193,r2
	ld %33569792,r3
	ld %1048576,r4
	ld %7671039,r5
	ld %1048576,r6
	ld %7865200,r7

l1: live %42
	live %42
	live %42
	live %42
	live %42
	live %42
	live %42
	live %42
	live %42
	live %42
	live %42
	live %42
	live %42
	live %42

live: live %42
	zjmp %:live

l2: live %42
	live %42
	add r4,r5,r5
	add r6,r7,r7
	st r7,13
	st r5,13
	st r2,120
	st r3,117
	fork %:l1
