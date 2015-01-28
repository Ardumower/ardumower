(*
  Ardumower (www.ardumower.de)
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*)

unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, TAGraph, TASeries, Forms, Controls, Graphics,
  Dialogs, ExtCtrls, StdCtrls, math;

type

  { TForm1 }

  TForm1 = class(TForm)
    ButtonStart: TButton;
    Chart1: TChart;
    Chart1LineSeries1: TLineSeries;
    Chart2LineSeries1: TLineSeries;
    Chart2: TChart;
    Chart3LineSeries1: TLineSeries;
    Chart3: TChart;
    Chart4LineSeries1: TLineSeries;
    Chart4: TChart;
    CheckBoxBField: TCheckBox;
    PaintBox1: TPaintBox;
    Timer1: TTimer;
    procedure ButtonStartClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure PaintBox1Paint(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

Type
  StateType = ( FORW, REV, ROLL );

var
  Form1: TForm1;
  run: boolean;
  list: array of TPoint;
  bfield: array of array of real;
  dir: real;
  speed: real;
  realpos: tpoint;
  bfieldimg: timage;
  plotIdx: integer;
  state: StateType;
  stateTime: real;


implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.FormCreate(Sender: TObject);
var
  i,x,y: integer;
  x1,y1:integer;
  y2,x2:integer;
  dx, dy: integer;
  px, py: integer;
  len: integer;
  deltax, deltay: integer;
  r, phi, b: real;
  cx, cy, xend: integer;
  v: byte;
begin
  run:=true;
  state:=FORW;
  stateTime:=0;
  plotIdx:=0;
  bfieldimg:=timage.create(self);
  bfieldimg.width:=paintbox1.width;
  bfieldimg.height:=paintbox1.height;

  realpos.x:=50;
  realpos.y:=50;
  speed := 0;
  dir := PI/8;

  setlength(list, 5);
  list[0].x := 30;
  list[0].y := 35;

  list[1].x := 400;
  list[1].y := 40;

  list[2].x := 410;
  list[2].y := 110;

  list[3].x := 210;
  list[3].y := 250;

  list[4].x := 50;
  list[4].y := 310;


  setlength(bfield, paintbox1.height);
  for y:=0 to length(bfield)-1 do
  begin
    setlength(bfield[y], paintbox1.width);
    for x:=0 to length(bfield[y])-1 do bfield[y][x]:=0;
  end;

  x1:=list[length(list)-1].x;
  y1:=list[length(list)-1].y;

  for i:=0 to length(list)-1 do
  begin
    x2:=list[i].x;
    y2:=list[i].y;

    dx := (x2-x1);
    dy := (y2-y1);
    len:=round(sqrt( dx*dx + dy*dy ));

    phi := arctan2(dy,dx);
    for y:=-200 to 200 do
    begin
      for x:=-100 to len*2+100-1 do
      begin
        px:= round(x1 + cos(phi)*x/2 - sin(phi)*y);
        py:= round(y1 + sin(phi)*x/2 + cos(phi)*y);
        xend := round(max(0, min(len, x/2)));
        cx := round(x1 + cos(phi)*xend);
        cy := round(y1 + sin(phi)*xend);
        if (py >= 0) and (py < length(bfield))
           and (px >=0) and (px < length(bfield[py])) then
        begin
          r := Max(0.000001, sqrt( (cx-px)*(cx-px) + (cy-py)*(cy-py) ) );
          b:=1000/(2*PI*r);
          if (y<=0) or (bfield[py][px] < 0) then
          begin
            b:=b*-1;
            bfield[py][px] :=  min(bfield[py][px], b);
          end else bfield[py][px] := max(bfield[py][px], b);
          //bfield[py][px] += b;
          //showmessage( floattoStr( bfield[py][px] ) );
        end;
      end;
    end;
    x1:=x2;
    y1:=y2;
  end;

  for y:=0 to bfieldimg.Height-1 do
  begin
    for x:=0 to bfieldimg.width-1 do
    begin
      b:=30 + 30*sqrt( abs(bfield[y][x]));
      //b:=10 + bfield[y][x];
      v:=min(255, max(0, round(b)));
      if (bfield[y][x] <= 0)then
        bfieldimg.Canvas.Pixels[x,y]:=RGBToColor(255-v,255-v,255)
      else
        bfieldimg.Canvas.Pixels[x,y]:=RGBToColor(255,255-v,255-v);
    end;
  end;

  (*x:=list[length(list)-1].x;
  y:=list[length(list)-1].y;
  bfieldimg.Canvas.MoveTo(x+1,y+1);
  bfieldimg.Canvas.Pen.Color := clRed;
  for i:=0 to length(list)-1 do
  begin
    x:=list[i].x;
    y:=list[i].y;
    bfieldimg.canvas.lineto(x+1,y+1);
  end;*)
end;

procedure TForm1.ButtonStartClick(Sender: TObject);
begin
  run:=not run;
  if (run) then ButtonStart.caption:='Stop'
    else ButtonStart.caption:='Start';
end;

procedure drawLine(canvas: tcanvas; cx: integer; cy: integer; phi: real;
    x1: integer; y1: integer;
    x2: integer; y2: integer);
var
  px,py: integer;
begin
  px:= round(cx + cos(phi)*x1 - sin(phi)*y1);
  py:= round(cy + sin(phi)*x1 + cos(phi)*y1);
  canvas.moveto(px, py);
  px:= round(cx + cos(phi)*x2 - sin(phi)*y2);
  py:= round(cy + sin(phi)*x2 + cos(phi)*y2);
  canvas.lineto(px, py );
end;

procedure TForm1.PaintBox1Paint(Sender: TObject);
begin
  paintbox1.canvas.Pen.Width:=3;
  if CheckBoxBField.checked then paintbox1.Canvas.draw(0,0, bfieldimg.Picture.Graphic);
  paintbox1.canvas.ellipse(realpos.x-10,realpos.y-10,realpos.x+10,realpos.y+10);
  drawLine(paintbox1.canvas, realpos.x, realpos.y, dir, -15, -10, 5,-10);
  drawLine(paintbox1.canvas, realpos.x, realpos.y, dir, -15,  10, 5, 10);
end;



procedure TForm1.Timer1Timer(Sender: TObject);
var
  b, dt: real;
begin
  if not run then exit;
  dt:=timer1.Interval / 1000;
  case state of
    FORW: speed := 40;
    REV: begin
           speed := -40;
           if stateTime > 0.5 then
           begin
             state:=ROLL;
             stateTime:=0;
           end;
         end;
    ROLL: begin
            speed:=40;
            dir += PI/8;
            if (dir > 2*PI) then dir -= 2*PI;
            if (dir < -2*PI) then dir += 2*PI;
            if stateTime > 0.7 then
            begin
              state:=FORW;
              stateTime:=0;
            end;
           end;
  end;
  realpos.x += round( cos(dir) * speed * dt );
  realpos.y += round( sin(dir) * speed * dt );

  if (realpos.x < 30) or (realpos.x >= paintbox1.Width-30)
    or (realpos.y < 30) or (realpos.y >= paintbox1.height-30) then
  begin
    state:=REV;
    stateTime:=0;
  end;

  if (realpos.y >= 0) and (realpos.y < length(bfield))
     and (realpos.x >=0) and (realpos.x < length(bfield[realpos.y])) then
  begin
    b:=max(-2, min(15, bfield[realpos.y][realpos.x]));
    if (b < 0) then
    begin
      state:=REV;
      stateTime:=0;
    end;
    //Chart1LineSeries1.AddXY(plotIdx, b);
    //if (chart1LineSeries1.Count > 10) then Chart1LineSeries1.Delete(0);

    Chart2LineSeries1.AddXY(plotIdx, b);
    if (chart2LineSeries1.Count > 150) then Chart2LineSeries1.Delete(0);

    Chart3LineSeries1.AddXY(plotIdx, dir);
    if (chart3LineSeries1.Count > 150) then Chart3LineSeries1.Delete(0);

    Chart4LineSeries1.AddXY(plotIdx, speed);
    if (chart4LineSeries1.Count > 150) then Chart4LineSeries1.Delete(0);

    inc(plotIdx);
  end;
  paintbox1.Repaint;
  stateTime += dt;
end;

end.


