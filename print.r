

Data <- matrix(Data,8,16,byrow=TRUE)
par(mai=c(0,0,0,0))
plot(c(0,16),c(0,8),type="n",axes=FALSE,ann=FALSE)
min <- 0

for ( i in 1:16) {
	for (j in 1:8 ) {
		if ( log(Data[9-j,17-i]) != log(2) && log(Data[9-j,17-i]) != log(0) && log((Data[9-j,17-i])) < min) {
			min =  log((Data[9-j,17-i]))
		}
	}
}


max <- min

for ( i in 1:16) {
	for (j in 1:8 ) {
		if ( log(Data[9-j,17-i]) != log(2) && log(Data[9-j,17-i]) != log(0) && log((Data[9-j,17-i])) > max) {
			max =  log((Data[9-j,17-i]))
		}
	}
}


for ( i in 1:16) {
	for (j in 1:8 ) {
		if ( Data[9-j,17-i] == 2 ) {
			polygon(c(17-i-1,17-i-1,17-i,17-i),c(j-1,j,j,j-1),col=rgb(0,0,0,maxColorValue=255),border="black")
		} else if ( Data[9-j,17-i] == 0 ) {
			polygon(c(17-i-1,17-i-1,17-i,17-i),c(j-1,j,j,j-1),col=rgb(255,255,255,maxColorValue=255),border="black")
		} else if ( min == max ) {
			polygon(c(17-i-1,17-i-1,17-i,17-i),c(j-1,j,j,j-1),col=rgb(255, 0, 0 ,maxColorValue=255),border="black")
		} else {
			polygon(c(17-i-1,17-i-1,17-i,17-i),c(j-1,j,j,j-1),col=rgb(255, 250*( (log(Data[9-j,17-i])-max)*(1/(min-max)) ), 250*( (log(Data[9-j,17-i])-max)*(1/(min-max)) ),maxColorValue=255),border="black")
		}

	}
}

polygon(c(0.25,0.25,0.75,0.75),c(2.25,2.75,2.75,2.25),col=rgb(175,175,0,maxColorValue=255),border=NA)
polygon(c(15.25,15.25,15.75,15.75),c(4.25,4.75,4.75,4.25),col=rgb(175,175,0,maxColorValue=255),border=NA)

polygon(c(pos1[1]+0.25,pos1[1]+0.25,pos1[1]+0.75,pos1[1]+0.75),c(pos1[2]+0.25,pos1[2]+0.75,pos1[2]+0.75,pos1[2]+0.25),col=rgb(0,200,200,maxColorValue=255),border=NA)
polygon(c(pos2[1]+0.25,pos2[1]+0.25,pos2[1]+0.75,pos2[1]+0.75),c(pos2[2]+0.25,pos2[2]+0.75,pos2[2]+0.75,pos2[2]+0.25),col=rgb(50,0,0,maxColorValue=255),border=NA)

polygon(c(2.35,2.5,2.65),c(7.35,7.65,7.35),col=rgb(0,200,0,maxColorValue=255),border=NA)
polygon(c(5.35,5.5,5.65),c(5.35,5.65,5.35),col=rgb(0,200,0,maxColorValue=255),border=NA)
polygon(c(4.35,4.5,4.65),c(3.35,3.65,3.35),col=rgb(0,200,0,maxColorValue=255),border=NA)
polygon(c(6.35,6.5,6.65),c(0.35,0.65,0.35),col=rgb(0,200,0,maxColorValue=255),border=NA)
polygon(c(11.35,11.5,11.65),c(6.35,6.65,6.35),col=rgb(0,200,0,maxColorValue=255),border=NA)
polygon(c(11.35,11.5,11.65),c(4.35,4.65,4.35),col=rgb(0,200,0,maxColorValue=255),border=NA)
polygon(c(10.35,10.5,10.65),c(2.35,2.65,2.35),col=rgb(0,200,0,maxColorValue=255),border=NA)


dev.off()
