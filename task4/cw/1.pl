

use Digest::MD5 qw(md5); 

for(1..256*256*256)
{
	$a= md5($_);
	print $a, " ", $_, "\n" if(substr($a, -2) eq "\",");
}
