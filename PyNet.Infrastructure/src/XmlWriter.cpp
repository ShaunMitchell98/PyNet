#include "XmlWriter.h"

namespace PyNet::Infrastructure {

	XmlWriter::XmlWriter(string_view filePath) {
		_stream = ofstream(filePath.data(), ios_base::app);
	}

	std::unique_ptr<XmlWriter> XmlWriter::Create(string_view filePath) {
		auto network = make_unique<XmlWriter>(filePath);
		network->WriteDeclaration();
		return std::move(network);
	}

	void XmlWriter::WriteDeclaration() {
		_stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	}

	void XmlWriter::StartElement(string_view name) {
		_stream << "<";
		_stream << name;
		_stream << ">\n";
		_openElements.push(name);
	}

	void XmlWriter::WriteString(string_view value) {
		_stream << value;
	}

	void XmlWriter::EndElement() {
		auto name = _openElements.top();
		_stream << "</";
		_stream << name;
		_stream << ">\n";
		_openElements.pop();
	}
}
