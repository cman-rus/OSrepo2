
print "Begin testing...\n\n";

for(8..11)
{
	$s=$_;
	print "-------------------------------------------\nSize: $s\n";

	open F, ">main.h";
        print F "const int size = $s;\nconst int sT = 0;";
        close F;

	`make`;
	print "\tR:";
        print `time ./main`;
	print "\n";
	for(1..7)
	{
		$st = $_;
		open F, ">main.h";
		print F "const int size = $s;\nconst int sT = $st;";
		close F;

		`make`;
		
		print "\tT=$st:";
		print `time ./main 2`;
                print "\tTmy=$st:";
                print `time ./main 2 2`;
		print "\n";
	}
}
