
void Create()
{
	imageMerger = new ImageMerger(this);
	colorReducer = new ColorReducer(this);
	histo = new Histogramer(this);

	imageViewer = new ImageViewer;
	histogramGraph = new HistogramGraph;

	connect(colorReducer, SIGNAL(output(const MonoBuffer&)),
			histo, SLOT(input(const MonoBuffer&)));
	connect(colorReducer, SIGNAL(output(const MonoBuffer&)),
			imageViewer, SLOT(setImage(const MonoBuffer&)));
	connect(histo, SIGNAL(output(const HistogramData&)),
			histogramGraph, SLOT(updateGraph(const HistogramData&)));

}


void Inspect(void)
{
	// 모든 image processor 는 부모 QObject에 대하여 아래의 연결을 수행.
	//
	// this->connect(longDiffer, SIGNAL(processFailed(const QString&)),
	// 				  SLOT(reportError(const QString&)));

	// ImageProcessor::link(ImageProcessor& prevObj) 를 통해
	//  - 앞 객체의 resetted() 시그널은 다음 객체의 reset() 슬롯에 연결한다.(각 객체의 임시상태 갱신)
	//  - 앞 객체의 processed() 시그널은 다음 객체의 process() 슬롯에 연결한다.(입/출력의 연계)
	// 할수 있도록 하여야 한다.

	// N개 이상의 객체로 부터 N번의 processed()가 확인되어야 process() 하는 객체를 위해서는
	// 별도의 ProcessMerger 객체의 도입이 필요.(입 출력의 동기화)

	imageResizer = new ImageResizer(this);
	{
		imageResizer->setRatio(8);
	}

	pitchDetector = new AdaptivePitchDetector(this);
	{
		pitchDetector->connect(imageResizer, SIGNAL(output(const MonoBuffer&)),
							   SLOT(input(const MonoBuffer&)));

		pitchDetector->link(imageResizer);
	}

	intensityCorrector = new LutProcessor(this);
	{
		// intensityCorrector->setUp(lookupTable);
		intensityCorrector->connect(imageResizer, SIGNAL(output(const MonoBuffer&)),
									SLOT(setImage(const MonoBuffer&)));
		intensityCorrector->connect(pitchDetector, SIGNAL(processed()),
									SLOT(process()));

		intensityCorrector->link(pitchDetector);
	}

	imageDiffer = new ImageDiffer(this);
	{
		imageDiffer->connect(intensityCorrector, SIGNAL(output(const MonoBuffer&)),
							 SLOT(input(const MonoBuffer&)));
		imageDiffer->connect(pitchDetector, SIGNAL(onPitchCalculated(double)),
							 SLOT(setPitch(double)));
		imageDiffer->link(pitchDetector);
	}

	pitchCorrector = new LongPitchCorrector(this);
	{
		pitchCorrector->connect(intensityCorrector, SIGNAL(output(const MonoBuffer&)),
								SLOT(setImage(const MonoBuffer&)));
		pitchCorrector->link(imageDiffer);
	}

	longDiffer = new ImageLongDiffer(this);
	{
		longDiffer->connect(intensityCorrector, SIGNAL(output(const MonoBuffer&)),
							SLOT(setImage(const MonoBuffer&)));
		longDiffer->connect(pitchCorrector, SIGNAL(pitchCorrected(double)),
							SLOT(setPitch(double)));
		longDiffer->link(pitchCorrector);
	}

	binarier = new BinaryImageMaker(this);
	{
		binarier->connect(imageDiffer, SIGNAL(output(const MonoBuffer&)),
						  SLOT(setDiffImage(const MonoBuffer&)));
		binarier->connect(longDiffer, SIGNAL(output(const MonoBuffer&)),
						  SLOT(setLongDiffImage(const MonoBuffer&)));
		binarier->link(longDiffer);
	}

	labeler = new ImageLabeler(this);
	{
		labeler->connect(imageResizer, SIGNAL(output(const MonoBuffer&)),
						 SLOT(setOriginalImage(const MonoBuffer&)));
		labeler->connect(binarier, SIGNAL(output(const MonoBuffer&)),
						 SLOT(setBinaryImage(const MonoBuffer&)));
		labeler->link(binarier);
	}

	imageResizer->reset(); // 줄줄이 모든 연결된 객체의 reset()이 호출.
	imageResizer->process(); // 줄줄이 모든 연결된 객체의 reset()이 호출.
}
