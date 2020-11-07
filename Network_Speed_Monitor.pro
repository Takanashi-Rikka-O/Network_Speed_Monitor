								Project<Network_Speed_Monitor>

Description:
	nsm(Network_Speed_Monitor) is a simply program respones to detecting network speed on this host.It will read data from /proc/net/dev and analyzes 
	these data,output result to tty.

Design reason:
	I want to have a program help me to know network speed on my machine.Of course,i have other way to instead design a new program.But i want to 
	do a tesing for myself.

Structure:
	Program will use C++ to be designed.

	Abstract monitor as a class.Class should to continuous output information.And also have a way to specify the ethernetwork
	interface card.Program no ncurses library to format output on tty.The less unit use KiB/s.(No unit converting)

	
	NIC-Specify.
	Option resolving.
	Received Information buff.	Input
	Sent Information buff.		Output
	Reading buff.
	FlowI and FlowJ.

	Speed detecting :
		Set i j is the times and not a same time.and j=i+1.
		Set n1 n2 is the flows at the times i and j.
		i->n1
		j->n2
		Speed=n2-n1/UNIT (KiB/s)

	i<-j,n1<-n2.
	j<-j+1,n2<-new.
		-- To next.

	Define Monitor class:
		Data member:
			NIC_Name;
			InputInfo;
			OutputInfo;
			FlowI;
			FlowJ;
			Reading buffer;
			DataFileName;
			FileInputObject;

		Method:
			Build;

			Set NIC_Name;
			Get memory for buff;
			Read data;
			Resolve data;
			Main working proreduce;

			Clear;
			

Logic order:
	main function can use specified arguments to create a monitor.And then it can invokes Main working proreduce to start moniting.
	Monitor class must use the arguments to build itself,if happened any error,it must exit and set error value.So,main function can checking this 
	value to determines that Monitor was normally started.
	After main invoked Main working proreduce,by the time,monitor will start detecting on the device.

	main:
		Check command line arguments.
		declare class object with specified arguments.
		checking error value.Error then quit.
		Invokes Main working proreduce.
		Get signal to exit.

	Monitor:
		use the arguments to builds itself.If failed,set error value and stop init.
		wait main invoking.
		entry main working proreduce.
		Get signal to exit.
		

Feature design:
	Set NIC_Name and can hand over to build method.Alloc memory and open file also can hand over to builder,too.
	Close file and recycle memory will responed by Cleaner.

	Command line parameter analyzing by main function.
	Defined options : -h (get help) -i dev (specify the device name)
	Does not set signal capturer.

Develop environment:

	CentOS 7
	Linux 3.10
	glibc 2.17

Debug or Other:

	TODO:
		# If i should design a new feature for make interval second becomes to selectable.

Complement:

	# Style of the /proc/net/dev information.

Inter-|   Receive                                                |  Transmit
 face |bytes    packets errs drop fifo frame compressed multicast|bytes    packets errs drop fifo colls carrier compressed
wlp3s0: 29976679   32490    0    0    0     0          0         0  4256061   29167    0    0    0     0       0          0
    lo:      49       1    0    0    0     0          0         0       49       1    0    0    0     0       0          0
enp2s0:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0


Version:
	0.0.1
