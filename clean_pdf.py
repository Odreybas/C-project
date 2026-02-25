import PyPDF2
import re

# Function to remove Unicode characters from text
def remove_unicode(text):
    # Use regex to remove characters that are not ASCII
    return re.sub(r'[^\x00-\x7F]+', '', text)

# Function to process the PDF file
def process_pdf(pdf_path, output_path):
    with open(pdf_path, 'rb') as file:
        reader = PyPDF2.PdfFileReader(file)
        writer = PyPDF2.PdfFileWriter()

        for page_num in range(reader.getNumPages()):
            page = reader.getPage(page_num)
            text = page.extractText()
            clean_text = remove_unicode(text)
            # Create a new page with clean text (if needed, requires adjustments)
            # For simplicity, here just adding the original page
            writer.addPage(page)

        with open(output_path, 'wb') as output_file:
            writer.write(output_file)

# Specify paths
input_pdf = 'fortune line code.pdf'
output_pdf = 'cleaned_fortune_line_code.pdf'
process_pdf(input_pdf, output_pdf)
