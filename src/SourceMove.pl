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
    die;
    my $command = "rm Game/Game$suffix.cpp";
    if (system($command) != 0)
    {
        print "'$command' failed\n";
    }
    $command = "rm Game/Game$suffix.h";
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



