#include "labelingChang2015.h"

#include <stdint.h>

using namespace cv;
using namespace std;

//int iCCIT (int* img, int* imgOut, unsigned char byF, int *numLabels, int w, int h, int ws, int wd);
//
//int CCIT  (int* srcImage, int* dstImage, unsigned char byForeground, int *numLabels, int w, int h, int ws, int wd)  {
//
//	if(srcImage == NULL || dstImage == NULL)
//		return 1;
//    iCCIT ( srcImage, dstImage, byForeground, numLabels, w, h, ws, wd);
//	return 0;
//}

/*
int CCIT(const Mat1b& img, Mat1i& imgOut) {

    unsigned char byF = 1; 
    
    //int *numLabels, int w, int h, int ws, int wd
	
    imgOut = Mat1i(img.size());

    int w = imgOut.cols, h = imgOut.rows;
    int wd, ws;
    ws = img.step;
    wd = imgOut.step;

    int imgElemSize = img.elemSize();
    int imgOutElemSize = imgOut.elemSize();

    int m = 1;
	int *aRTable = new int[w*h/4];
	int *aNext = new int[w*h/4];
	int *aTail = new int[w*h/4];

	int lx,u,v,k;
	
	#define condition_b1 img(y,x)==byF
	#define condition_b2 x+1<w && img(y,x+1)==byF
	#define condition_b3 y+1<h && img(y+1,x)==byF 
#define condition_b4 x+1<w && y+1<h && img(y+1,x+1)==byF 
#define condition_u1 y-1>0 && x-1>0 && img(y-1,x-1)==byF
	#define condition_u2 y-1>0 && img(y-1,x)==byF
	#define condition_u3 x+1<w && y-1>0 && img(y-1,x+1)==byF
#define condition_u4 x+2<w && y-1>0 && img(y-1,x+2)==byF 
	#define assign_S imgOut(y,x) = imgOut(y,x-2)
#define assign_P imgOut(y,x) = imgOut(y-2,x-2)
#define assign_Q imgOut(y,x) = imgOut(y-2,x)
#define assign_R imgOut(y,x) = imgOut(y-2,x+2)
#define newlabel imgOut(y,x) = m
	#define assign_lx imgOut(y,x) = lx
	#define load_lx u = aRTable[lx]
#define load_Pu u = aRTable[imgOut(y-2,x-2)]
#define load_Pv v = aRTable[imgOut(y-2,x-2)]
	#define load_Qu u = aRTable[imgOut(y-2,x)]
	#define load_Qv v = aRTable[imgOut(y-2,x)]
	#define load_Qk k = aRTable[imgOut(y-2,x)]
#define load_Rv v = aRTable[imgOut(y-2,x+2)]
#define load_Rk k = aRTable[imgOut(y-2,x+2)]
	#define newlabelprocess lx = newlabel; 	aRTable[m] = m;  aNext[m] = -1;  aTail[m] = m;	m = m + 1;
	#define reslove2(u, v); 		if (u<v) { int i = v; 	while (i>-1) {	aRTable[i] = u;	i = aNext[i];	}	aNext[aTail[u]] = v; aTail[u] = aTail[v]; 	}else if (u>v) {	int i = u; 	while (i>-1) { aRTable[i] = v; 	i = aNext[i]; }	aNext[aTail[v]] = u; aTail[v] = aTail[u]; };
    #define reslove3(u, v, k); 		if (u<v) { int i = v; 	while (i>-1) { 	aRTable[i] = u; i = aNext[i]; 	} 	aNext[aTail[u]] = v; aTail[u] = aTail[v];  k = aRTable[k]; if (u<k) { int i = k; 	while (i>-1) { 	aRTable[i] = u; i = aNext[i]; } aNext[aTail[u]] = k;  aTail[u] = aTail[k]; 	} else if (u>k) { int i = u;   while (i>-1) { aRTable[i] = k; i = aNext[i]; } aNext[aTail[k]] = u; 	aTail[k] = aTail[u]; } 	} else if (u>v) { int i = u; while (i>-1) { aRTable[i] = v;    i = aNext[i]; 	} 	aNext[aTail[v]] = u;  aTail[v] = aTail[u];	k = aRTable[k];	if (v<k) { int i = k; while (i>-1) { aRTable[i] = v;  i = aNext[i];	}   	   aNext[aTail[v]] = k; aTail[v] = aTail[k]; } else if (v>k) { int i = v;	while (i>-1) {	aRTable[i] = k; 	i = aNext[i]; } aNext[aTail[k]] = v; aTail[k] = aTail[v]; } }else { k = aRTable[k]; if (u<k) {	int i = k; while (i>-1) { aRTable[i] = u; i = aNext[i];	} aNext[aTail[u]] = k;	aTail[u] = aTail[k]; }else if (u>k) { int i = u;	while (i>-1) {	aRTable[i] = k;	i = aNext[i]; } aNext[aTail[k]] = u; aTail[k] = aTail[u]; }; };
	
	bool nextprocedure2;

	//prcess first two rows
	for(int x=0; x<w; x+=2) {
		int y = 0;
		if(condition_b1){
			newlabelprocess;
			if(condition_b2 || condition_b4)
				nextprocedure2 = true;
			else 
				nextprocedure2 = false;
		}else if(condition_b2){
			newlabelprocess;
			nextprocedure2 = true;
		}else if(condition_b3){
			newlabelprocess;
			if(condition_b4)
				nextprocedure2 = true;
			else 
				nextprocedure2 = false;
		}else if(condition_b4){
			newlabelprocess;
			nextprocedure2 = true;
		}else{
			nextprocedure2 = false;
		}

		while(nextprocedure2 && x+2<w){
			x = x + 2;
			if(condition_b1){
				assign_lx;
				if(condition_b2 || condition_b4)
					nextprocedure2 = true;
				else 
					nextprocedure2 = false;
			}else if(condition_b2){
				
				if(condition_b3){
					assign_lx;
				}else{
					newlabelprocess;
				}
				nextprocedure2 = true;
			}else if(condition_b3){
				assign_lx;
				if(condition_b4)
					nextprocedure2 = true;
				else 
					nextprocedure2 = false;
			}else if(condition_b4){
				newlabelprocess;
				nextprocedure2 = true;
			}else{
				nextprocedure2 = false;
			}
		
		}
	}
	

	for(int y=2; y<h; y+=2) {
		for(int x=0; x<w; x+=2) {
			if(condition_b1){
				if(condition_b2){
					if(condition_u2){
						lx = assign_Q;
						if(condition_u3){

						}else{
							if(condition_u4){
								load_lx; 
								load_Rv;
								reslove2(u, v);						
							}
						}
					}else if(condition_u3){
						lx = assign_Q;
						if(condition_u1){
							load_lx; 
							load_Pv;
							reslove2(u, v);
						}

					}else if(condition_u1){
						lx = assign_P;
						if(condition_u4){
							load_lx; 
							load_Rv;
							reslove2(u, v);
						}
					}else if(condition_u4){
						lx = assign_R;
					}else{
						newlabelprocess;
					}
					nextprocedure2 = true;
				}else{
					if(condition_u2){
						lx = assign_Q;					
					}else if(condition_u1){
						lx = assign_P;
						if(condition_u3){
							load_lx; 
							load_Qv;
							reslove2(u, v);
							
						}
					}else if(condition_u3){
						lx = assign_Q;
					}else{
						newlabelprocess;
					}
					if(condition_b4)
						nextprocedure2 = true;
					else
						nextprocedure2 = false;
				
				}			
			}else if(condition_b2){
				if(condition_u3){
					lx = assign_Q;	
				}else if(condition_u2){
					lx = assign_Q;	
					if(condition_u4){
						load_lx; 
						load_Rv;
						reslove2(u, v);
					}
				}else if(condition_u4){
					lx = assign_R;
				}else{
					newlabelprocess;
				}
				nextprocedure2 = true;
			}else if(condition_b3){
				newlabelprocess;
				if(condition_b4)
					nextprocedure2 = true;//
				else
					nextprocedure2 = false;
			}else if(condition_b4){
				newlabelprocess;
				nextprocedure2 = true;
			}else{
				nextprocedure2 = false;
			}
			
			while(nextprocedure2 && x+2<w){
				x = x + 2;
				if(condition_b1){
					
					assign_lx;
					if(condition_b2){
						if(condition_u2){	
							if(condition_u3){
								load_lx; 
								load_Qv;
								reslove2(u, v);
							}else{
								if(condition_u4){
									load_lx;
									load_Qv;
									load_Rk;
									reslove3(u, v, k); 								
								}else{
									load_lx; 
									load_Qv;
									reslove2(u, v);								
								}
							}
						
						}else if(condition_u3){
							if(condition_u1){
								load_lx;
								load_Pv;
								load_Qk;
								reslove3(u, v, k); 							
							}else{
								//reslove S, Q
								load_lx; 
								load_Qv;
								reslove2(u, v);
							}
						}else if(condition_u1){
							if(condition_u4){
								load_lx;
								load_Pv;
								load_Rk;
								reslove3(u, v, k); 
							}else{
								load_lx; 
								load_Pv;
								reslove2(u, v);
							}
						
						}else if(condition_u4){
							load_lx; 
							load_Rv;
							reslove2(u, v);
						}
						nextprocedure2 = true;
					}else{
						assign_lx;
						if(condition_u2){
							load_lx; 
							load_Qv;
							reslove2(u, v);
						}else if(condition_u1){
							if(condition_u3){	
								load_lx;
								load_Pv;
								load_Qk;
								reslove3(u, v, k); 
							}else{
								load_lx; 
								load_Pv;
								reslove2(u, v);					
							}						
						}else if(condition_u3){
							load_lx; 
							load_Qv;
							reslove2(u, v);
						}

						if(condition_b4)
							nextprocedure2 = true;//
						else
							nextprocedure2 = false;
					}			
				
				}else if(condition_b2){
					if(condition_b3){
						assign_lx;
						if(condition_u3){
							load_lx; 
							load_Qv;
							reslove2(u, v);
						}else if(condition_u2){								
							if(condition_u4){
								load_lx;
								load_Qv;
								load_Rk;
								reslove3(u, v, k); 							
							}else{
								load_lx; 
								load_Qv;
								reslove2(u, v);	
							}
						}if(condition_u4){
							load_lx; 
							load_Rv;
							reslove2(u, v);
						}
					}else{
						if(condition_u3){
							lx = assign_Q;	
						}else if(condition_u2){
							lx = assign_Q;	
							if(condition_u4){
								load_lx; 
								load_Rv;
								reslove2(u, v);
							}
						}else if(condition_u4){
							lx = assign_R;
						}else{
							newlabelprocess;
						}
					}
					
					nextprocedure2 = true;
				}else if(condition_b3){
					assign_lx ;
					if(condition_b4)
						nextprocedure2 = true;
					else
						nextprocedure2 = false;
				}else if(condition_b4){
					newlabelprocess;
					nextprocedure2 = true;
				}else{
					nextprocedure2 = false;
				}
			}
		}
	}
    //Renew label number
	int iCurLabel = 0;
	for (int i=1;i<m;i++) {
		if (aRTable[i]==i) {
			iCurLabel++;
			aRTable[i] = iCurLabel;			
		}
		else
			aRTable[i] = aRTable[aRTable[i]];
	}
	// SECOND SCAN 
	for(int y=0;y<h;y+=2) {
		for(int x=0;x<w;x+=2) {
			int iLabel = imgOut(y,x) ;
			if (iLabel>0) {
				iLabel = aRTable[iLabel];
				if (img(y,x)==byF)
					imgOut(y,x) = iLabel;
				else
					imgOut(y,x) = 0;
				if (x+1<w) {
					if (img(y,x+1)==byF)
						imgOut(y,x+1) = iLabel;
					else
						imgOut(y,x+1) = 0;
					if (y+1<h) {
						if (img(y+1,x)==byF)
							imgOut(y+1,x) = iLabel;
						else
							imgOut(y+1,x) = 0;
						if (img(y+1,x+1)==byF)
							imgOut(y+1,x+1) = iLabel;
						else
							imgOut(y+1,x+1) = 0;
					}
				}
				else if (y+1<h) {
					if (img(y+1,x)==byF)
						imgOut(y+1,x) = iLabel;
					else
						imgOut(y+1,x) = 0;
				}
			}
			else {
				imgOut(y,x) = 0;
				if (x+1<w) {
					imgOut(y,x+1) = 0;
					if (y+1<h) {
						imgOut(y+1,x) = 0;
						imgOut(y+1,x+1) = 0;
					}
				}
				else if (y+1<h) {
					imgOut(y+1,x) = 0;
				}
			}
		}
	}

	// output the number of labels
	//*numLabels = iCurLabel;
	delete [] aRTable;
	delete [] aNext;
	delete [] aTail;
	return ++iCurLabel;
}
*/

int CCIT(const Mat1b& img, Mat1i& imgOut) {

    unsigned char byF = 1;

    //int *numLabels, int w, int h, int ws, int wd

    imgOut = Mat1i(img.size(),0);

    int w = imgOut.cols, h = imgOut.rows;
    int wd, ws;
    ws = img.step;
    wd = imgOut.step;

    int imgElemSize = img.elemSize();
    int imgOutElemSize = imgOut.elemSize();

    int m = 1;
    int *aRTable = new int[w*h / 4];
    int *aNext = new int[w*h / 4];
    int *aTail = new int[w*h / 4];

    int lx, u, v, k;

    //cout << imgOut(0, 0); 

#define condition_b1 img_row[x]==byF
#define condition_b2 x+1<w && img_row[x+1]==byF   // add control condition
#define condition_b3 y+1<h && img_row_fol[x]==byF   // add control condition 
#define condition_b4 x+1<w && y+1<h && img_row_fol[x+1]==byF    // add control condition
#define condition_u1 y-1>0 && x-1>0 && img_row_prev[x-1]==byF    // add control consition
#define condition_u2 y-1>0 && img_row_prev[x]==byF  // add control consition
#define condition_u3 x+1<w && y-1>0 && img_row_prev[x+1]==byF   // add control consition
#define condition_u4 x+2<w && y-1>0 && img_row_prev[x+2]==byF   // add control consition
#define assign_S imgOut_row[x] = imgOut_row[x-2]
#define assign_P imgOut_row[x] = imgOut_row_prev_prev[x-2]
#define assign_Q imgOut_row[x] = imgOut_row_prev_prev[x]
#define assign_R imgOut_row[x] = imgOut_row_prev_prev[x+2]
#define newlabel imgOut_row[x] = m
#define assign_lx imgOut_row[x] = lx
#define load_lx u = aRTable[lx]
#define load_Pu u = aRTable[imgOut_row_prev_prev[x-2]]
#define load_Pv v = aRTable[imgOut_row_prev_prev[x-2]]
#define load_Qu u = aRTable[imgOut_row_prev_prev[x]]
#define load_Qv v = aRTable[imgOut_row_prev_prev[x]]
#define load_Qk k = aRTable[imgOut_row_prev_prev[x]]
#define load_Rv v = aRTable[imgOut_row_prev_prev[x+2]]
#define load_Rk k = aRTable[imgOut_row_prev_prev[x+2]]
#define newlabelprocess lx = newlabel; 	aRTable[m] = m;  aNext[m] = -1;  aTail[m] = m;	m = m + 1;
#define reslove2(u, v); 		if (u<v) { int i = v; 	while (i>-1) {	aRTable[i] = u;	i = aNext[i];	}	aNext[aTail[u]] = v; aTail[u] = aTail[v]; 	}else if (u>v) {	int i = u; 	while (i>-1) { aRTable[i] = v; 	i = aNext[i]; }	aNext[aTail[v]] = u; aTail[v] = aTail[u]; };
#define reslove3(u, v, k); 		if (u<v) { int i = v; 	while (i>-1) { 	aRTable[i] = u; i = aNext[i]; 	} 	aNext[aTail[u]] = v; aTail[u] = aTail[v];  k = aRTable[k]; if (u<k) { int i = k; 	while (i>-1) { 	aRTable[i] = u; i = aNext[i]; } aNext[aTail[u]] = k;  aTail[u] = aTail[k]; 	} else if (u>k) { int i = u;   while (i>-1) { aRTable[i] = k; i = aNext[i]; } aNext[aTail[k]] = u; 	aTail[k] = aTail[u]; } 	} else if (u>v) { int i = u; while (i>-1) { aRTable[i] = v;    i = aNext[i]; 	} 	aNext[aTail[v]] = u;  aTail[v] = aTail[u];	k = aRTable[k];	if (v<k) { int i = k; while (i>-1) { aRTable[i] = v;  i = aNext[i];	}   	   aNext[aTail[v]] = k; aTail[v] = aTail[k]; } else if (v>k) { int i = v;	while (i>-1) {	aRTable[i] = k; 	i = aNext[i]; } aNext[aTail[k]] = v; aTail[k] = aTail[v]; } }else { k = aRTable[k]; if (u<k) {	int i = k; while (i>-1) { aRTable[i] = u; i = aNext[i];	} aNext[aTail[u]] = k;	aTail[u] = aTail[k]; }else if (u>k) { int i = u;	while (i>-1) {	aRTable[i] = k;	i = aNext[i]; } aNext[aTail[k]] = u; aTail[k] = aTail[u]; }; };

    bool nextprocedure2;

    int y = 0; // extract from the first for
    const uchar* const img_row = img.ptr<uchar>(y);
    const uchar* const img_row_fol = (uchar *)(((char *)img_row) + img.step.p[0]);
    uint* const imgOut_row = imgOut.ptr<uint>(y);
    //prcess first two rows
    // cout << "." << endl;
    for (int x = 0; x<w; x += 2) {

        if (condition_b1){
            newlabelprocess;
            if (condition_b2 || condition_b4)
                nextprocedure2 = true;
            else
                nextprocedure2 = false;
        }
        else if (condition_b2){
            newlabelprocess;
            nextprocedure2 = true;
        }
        else if (condition_b3){
            newlabelprocess;
            if (condition_b4)
                nextprocedure2 = true;
            else
                nextprocedure2 = false;
        }
        else if (condition_b4){
            newlabelprocess;
            nextprocedure2 = true;
        }
        else{
            nextprocedure2 = false;
        }

        while (nextprocedure2 && x + 2<w){
            x = x + 2;

            if (condition_b1){
                assign_lx;
                if (condition_b2 || condition_b4)
                    nextprocedure2 = true;
                else
                    nextprocedure2 = false;
            }
            else if (condition_b2){

                if (condition_b3){
                    assign_lx;
                }
                else{
                    newlabelprocess;
                }
                nextprocedure2 = true;
            }
            else if (condition_b3){
                assign_lx;
                if (condition_b4)
                    nextprocedure2 = true;
                else
                    nextprocedure2 = false;
            }
            else if (condition_b4){
                newlabelprocess;
                nextprocedure2 = true;
            }
            else{
                nextprocedure2 = false;
            }

        }
    }

    // cout << "." << endl;
    for (int y = 2; y<h; y += 2) {
        const uchar* const img_row = img.ptr<uchar>(y);
        const uchar* const img_row_prev = (uchar *)(((char *)img_row) - img.step.p[0]);
        const uchar* const img_row_fol = (uchar *)(((char *)img_row) + img.step.p[0]);
        uint* const imgOut_row = imgOut.ptr<uint>(y);
        uint* const imgOut_row_prev_prev = (uint *)(((char *)imgOut_row) - imgOut.step.p[0] - imgOut.step.p[0]);
        for (int x = 0; x<w; x += 2) {
            if (condition_b1){
                if (condition_b2){
                    if (condition_u2){
                        lx = assign_Q;
                        if (condition_u3){

                        }
                        else{
                            if (condition_u4){
                                load_lx;
                                load_Rv;
                                reslove2(u, v);
                            }
                        }
                    }
                    else if (condition_u3){
                        lx = assign_Q;
                        if (condition_u1){
                            load_lx;
                            load_Pv;
                            reslove2(u, v);
                        }

                    }
                    else if (condition_u1){
                        lx = assign_P;
                        if (condition_u4){
                            load_lx;
                            load_Rv;
                            reslove2(u, v);
                        }
                    }
                    else if (condition_u4){
                        lx = assign_R;
                    }
                    else{
                        newlabelprocess;
                    }
                    nextprocedure2 = true;
                }
                else{
                    if (condition_u2){
                        lx = assign_Q;
                    }
                    else if (condition_u1){
                        lx = assign_P;
                        if (condition_u3){
                            load_lx;
                            load_Qv;
                            reslove2(u, v);

                        }
                    }
                    else if (condition_u3){
                        lx = assign_Q;
                    }
                    else{
                        newlabelprocess;
                    }
                    if (condition_b4)
                        nextprocedure2 = true;
                    else
                        nextprocedure2 = false;

                }
            }
            else if (condition_b2){
                if (condition_u3){
                    lx = assign_Q;
                }
                else if (condition_u2){
                    lx = assign_Q;
                    if (condition_u4){
                        load_lx;
                        load_Rv;
                        reslove2(u, v);
                    }
                }
                else if (condition_u4){
                    lx = assign_R;
                }
                else{
                    newlabelprocess;
                }
                nextprocedure2 = true;
            }
            else if (condition_b3){
                newlabelprocess;
                if (condition_b4)
                    nextprocedure2 = true;//
                else
                    nextprocedure2 = false;
            }
            else if (condition_b4){
                newlabelprocess;
                nextprocedure2 = true;
            }
            else{
                nextprocedure2 = false;
            }

            while (nextprocedure2 && x + 2<w){
                x = x + 2;
                if (condition_b1){

                    assign_lx;
                    if (condition_b2){
                        if (condition_u2){
                            if (condition_u3){
                                load_lx;
                                load_Qv;
                                reslove2(u, v);
                            }
                            else{
                                if (condition_u4){
                                    load_lx;
                                    load_Qv;
                                    load_Rk;
                                    reslove3(u, v, k);
                                }
                                else{
                                    load_lx;
                                    load_Qv;
                                    reslove2(u, v);
                                }
                            }

                        }
                        else if (condition_u3){
                            if (condition_u1){
                                load_lx;
                                load_Pv;
                                load_Qk;
                                reslove3(u, v, k);
                            }
                            else{
                                //reslove S, Q
                                load_lx;
                                load_Qv;
                                reslove2(u, v);
                            }
                        }
                        else if (condition_u1){
                            if (condition_u4){
                                load_lx;
                                load_Pv;
                                load_Rk;
                                reslove3(u, v, k);
                            }
                            else{
                                load_lx;
                                load_Pv;
                                reslove2(u, v);
                            }

                        }
                        else if (condition_u4){
                            load_lx;
                            load_Rv;
                            reslove2(u, v);
                        }
                        nextprocedure2 = true;
                    }
                    else{
                        assign_lx;
                        if (condition_u2){
                            load_lx;
                            load_Qv;
                            reslove2(u, v);
                        }
                        else if (condition_u1){
                            if (condition_u3){
                                load_lx;
                                load_Pv;
                                load_Qk;
                                reslove3(u, v, k);
                            }
                            else{
                                load_lx;
                                load_Pv;
                                reslove2(u, v);
                            }
                        }
                        else if (condition_u3){
                            load_lx;
                            load_Qv;
                            reslove2(u, v);
                        }

                        if (condition_b4)
                            nextprocedure2 = true;//
                        else
                            nextprocedure2 = false;
                    }

                }
                else if (condition_b2){
                    if (condition_b3){
                        assign_lx;
                        if (condition_u3){
                            load_lx;
                            load_Qv;
                            reslove2(u, v);
                        }
                        else if (condition_u2){
                            if (condition_u4){
                                load_lx;
                                load_Qv;
                                load_Rk;
                                reslove3(u, v, k);
                            }
                            else{
                                load_lx;
                                load_Qv;
                                reslove2(u, v);
                            }
                        }if (condition_u4){
                            load_lx;
                            load_Rv;
                            reslove2(u, v);
                        }
                    }
                    else{
                        if (condition_u3){
                            lx = assign_Q;
                        }
                        else if (condition_u2){
                            lx = assign_Q;
                            if (condition_u4){
                                load_lx;
                                load_Rv;
                                reslove2(u, v);
                            }
                        }
                        else if (condition_u4){
                            lx = assign_R;
                        }
                        else{
                            newlabelprocess;
                        }
                    }

                    nextprocedure2 = true;
                }
                else if (condition_b3){
                    assign_lx;
                    if (condition_b4)
                        nextprocedure2 = true;
                    else
                        nextprocedure2 = false;
                }
                else if (condition_b4){
                    newlabelprocess;
                    nextprocedure2 = true;
                }
                else{
                    nextprocedure2 = false;
                }
            }
        }
    }
    // cout << "." << endl;
    //Renew label number
    int iCurLabel = 0;
    for (int i = 1; i<m; i++) {
        if (aRTable[i] == i) {
            iCurLabel++;
            aRTable[i] = iCurLabel;
        }
        else
            aRTable[i] = aRTable[aRTable[i]];
    }
    // cout << "." << endl;
    // SECOND SCAN 
    for (int y = 0; y<h; y += 2) {
        const uchar* const img_row = img.ptr<uchar>(y);
        const uchar* const img_row_fol = (uchar *)(((char *)img_row) + img.step.p[0]);
        uint* const imgOut_row = imgOut.ptr<uint>(y);
        uint* const imgOut_row_fol = (uint *)(((char *)imgOut_row) + imgOut.step.p[0]);
        for (int x = 0; x<w; x += 2) {
            int iLabel = imgOut_row[x];
            if (iLabel>0) {
                // cout << iLabel << "\n";
                iLabel = aRTable[iLabel];
                if (img_row[x] == byF)
                    imgOut_row[x] = iLabel;
                else
                    imgOut_row[x] = 0;
                if (x + 1<w) {
                    if (img_row[x + 1] == byF)
                        imgOut_row[x + 1] = iLabel;
                    else
                        imgOut_row[x + 1] = 0;
                    if (y + 1<h) {
                        if (img_row_fol[x] == byF)
                            imgOut_row_fol[x] = iLabel;
                        else
                            imgOut_row_fol[x] = 0;
                        if (img_row_fol[x + 1] == byF)
                            imgOut_row_fol[x + 1] = iLabel;
                        else
                            imgOut_row_fol[x + 1] = 0;
                    }
                }
                else if (y + 1<h) {
                    if (img_row_fol[x] == byF)
                        imgOut_row_fol[x] = iLabel;
                    else
                        imgOut_row_fol[x] = 0;
                }
            }
            else {
                imgOut_row[x] = 0;
                if (x + 1<w) {
                    imgOut_row[x + 1] = 0;
                    if (y + 1<h) {
                        imgOut_row_fol[x] = 0;
                        imgOut_row_fol[x + 1] = 0;
                    }
                }
                else if (y + 1<h) {
                    imgOut_row_fol[x] = 0;
                }
            }
        }
    }
    //cout << "." << endl;

    // output the number of labels
    //*numLabels = iCurLabel;
    delete[] aRTable; // add []
    delete[] aNext; // add []
    delete[] aTail; //add []
    return ++iCurLabel;
}