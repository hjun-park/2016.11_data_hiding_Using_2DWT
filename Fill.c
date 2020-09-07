extern const char *transform_black(unsigned char *bfx)
{
	Point pos1;         // x1, y1
	Point pos2;         // x2, y2
	sInfo info;         // width, height
	const char *errmsg;
	int temp;
	int init;


	fputs("\n", stdout);
	fputs("Width : ", stdout);
	scanf("%d", &info.width);
	fputs("Height : ", stdout);
	scanf("%d", &info.height);
	/*if(info.width > org.width || info.height > org.height){
	fputs("Exceed Size ", stdout);
	ERROR_ABORT(p_err_writeerr);
	}*/

	fputs("point1 pos(x1, y1) : ", stdout);
	scanf("%d %d", &pos1.xPos, &pos1.yPos);
	fputs("point2 pos(x2, y2) : ", stdout);
	scanf("%d %d", &pos2.xPos, &pos2.yPos);

	if (pos1.xPos > pos2.xPos) {
		temp = pos2.xPos;
		pos2.xPos = pos1.xPos;
		pos1.xPos = temp;
	}

	if (pos1.yPos > pos2.yPos) {
		temp = pos2.yPos;
		pos2.yPos = pos1.yPos;
		pos1.yPos = temp;
	}

	if (pos1.xPos > info.width || pos1.yPos > info.height || pos2.xPos > info.width || pos2.yPos > info.height) {
		return NULL;
	}
	else {
		init = pos1.yPos;
		for (; pos1.xPos <= pos2.xPos; pos1.xPos++) {
			for (; pos1.yPos <= pos2.yPos; pos1.yPos++) {
				if (pos1.xPos == pos2.xPos && pos1.yPos == pos2.yPos)
					break;
				bfx[info.width*pos1.yPos + pos1.xPos] = 0;
			}
			pos1.yPos = init;
		}
	}
}
