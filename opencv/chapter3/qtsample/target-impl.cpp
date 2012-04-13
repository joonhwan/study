
void Create()
{
	WImageProcessBlock* block = new ColorDetector;

	layout->addWidget(block->generateEditor());

	block->process(inputImage);
}
