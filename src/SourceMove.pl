#!/usr/bin/perl -w

my @fileList =
(
'Def',
'DefClient',
'DefServer',
'NetID',
'NetObject',
'NetUtils',
);

foreach my $suffix (@fileList)
{

    my $command = "mv Game/Game$suffix.cpp MustlGame/MustlGame$suffix.cpp";
    if (system($command) != 0)
    {
        print "'$command' failed\n";
    }
    $command = "mv Game/Game$suffix.h MustlGame/MustlGame$suffix.h";
    if (system($command) != 0)
    {
        print "'$command' failed\n";
    }
    $command = "cvs remove Game/Game$suffix.cpp";
    if (system($command) != 0)
    {
        print "'$command' failed\n";
    }
    $command = "cvs remove Game/Game$suffix.h";
    if (system($command) != 0)
    {
        print "'$command' failed\n";
    }

}
print "Done\n";



