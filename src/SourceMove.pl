#!/usr/bin/perl -w

my @fileList =
(
'ChequePoint',
'Contract',
'Data',
'DataUtils',
'FloorDesigner',
'FloorMap',
'LightLinks',
'Info',
'Map',
'MapArea',
'MapPoint',
'MessageControlData',
'Motion',
'MotionSpec',
'OverPlot',
'SolidMap',
'SpacePoint',
'Test',
'TileMap',
'TileSpec',
'TileTraits',
'Timer',
'View',
'WebCommands'
);

foreach my $suffix (@fileList)
{
    my $command = "mv Game/Game$suffix.cpp Infernal/Infernal$suffix.cpp";
    if (system($command) != 0)
    {
        print "'$command' failed\n";
    }
    my $command = "mv Game/Game$suffix.h Infernal/Infernal$suffix.h";
    if (system($command) != 0)
    {
        print "'$command' failed\n";
    }
}
print "Done\n";
