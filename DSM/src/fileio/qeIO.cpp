#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif
#include <vector>
#include <string>
#include <QtCore/QTextStream>
#include <QtWidgets/QFileDialog>
#include <QtCore/QTextCodec>
#include <QtCore/QFile>
#include "qeIO.h"

qeRW::qeRW()
{

}

qeRW::~qeRW()
{

}

bool qeRW::loadIN(QString& path, std::vector<Particle> &out_atoms, glm::dmat3 &out_cell)
{
	int natoms = 0;
	float cell_scale = 1.0f;

	if (out_atoms.size() > 0)
	{
		out_atoms.clear();
	}
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}
	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		if (line.contains("nat"))
		{
            natoms = line.split("=",QString::SkipEmptyParts)[1].toInt();
		}
		if (line.contains("CELL_PARAMETERS"))
		{
			for (uint i = 0 ; i<3;i++)
			{

				QStringList cell_line = in.readLine().split(QRegExp("\\s+"), QString::SkipEmptyParts);
				if (abs(cell_line[0].toFloat()) > 0.0001)
				{
					out_cell[i][0] = cell_line[0].toDouble();
				}
				else
					out_cell[i][0] = 0.0f;
				if (abs(cell_line[1].toFloat()) > 0.0001)
				{
					out_cell[i][1] = cell_line[1].toDouble();
				}
				else
					out_cell[i][1] = 0.0f;
				if (abs(cell_line[2].toFloat()) > 0.0001)
				{
					out_cell[i][2] = cell_line[2].toDouble();
				}
				else
					out_cell[i][2] = 0.0f;
			}
		}
		if (line.contains("ATOMIC_POSITIONS"))
		{
			elements::Element element;
			for (int i =0 ; i<natoms;i++)
			{
				QStringList atom_line = in.readLine().split(QRegExp("\\s+"), QString::SkipEmptyParts);
				if (atom_line.size()<4)
				{
					break;
				}
				if (atom_line[0].size()>2)
				{
					atom_line[0] = atom_line[0].left(2);
				}
				for (unsigned int i = 0; i < elements::ELEMENTS.size(); i++)
				{
					if (atom_line[0]==QString(elements::ELEMENTS[i].Symbol.c_str()))
					{
						element = elements::ELEMENTS[i];
					}
				}
				out_atoms.push_back(Particle(element, out_cell*glm::vec3(atom_line[1].toDouble(), atom_line[2].toDouble(), atom_line[3].toDouble())));
			}
		}
	}
	return true;
}

bool qeRW::loadOUT(QString& path, std::vector <Particle> &out_atoms, glm::dmat3 &out_cell)
{
	return true;
}

bool qeRW::saveStructure(Structure* structure,bool saveAs)
{
	QTextCodec *codec = QTextCodec::codecForLocale();
	QFile outFile;
	QFile inFile;
	if (!saveAs)
	{
		if (structure->file != NULL)
		{
			outFile.setFileName(structure->file + QString("_tmp"));
			inFile.setFileName(structure->file);
		}
		else
		{
#ifdef __APPLE__
            CFURLRef appUrlRef;
	    	appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(),CFSTR("/src/fileio/templates/pw.in"),NULL,NULL);
	    	CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
	    	const char* pathString = CFStringGetCStringPtr(filePathRef,kCFStringEncodingUTF8);
#else 
			const char* pathString = "/src/fileio/templates/pw.in";
#endif
            inFile.setFileName(pathString);
#ifdef __APPLE__
            CFRelease(appUrlRef);
	    	CFRelease(filePathRef);
#endif
			QString filename = QFileDialog::getSaveFileName(NULL, QFileDialog::tr("Save File"), "", QFileDialog::tr("Text files(*.txt;*.in)"));
			outFile.setFileName(filename);
			structure->file = filename;
		}
	}
	else
	{
		if (structure->file != NULL)
		{
			QString filename = QFileDialog::getSaveFileName(NULL, QFileDialog::tr("Save File"), "", QFileDialog::tr("Text files(*.txt;*.in)"));
			outFile.setFileName(filename);
			inFile.setFileName(structure->file);
			structure->file = filename;

		}
		else
		{

#ifdef __APPLE__
            CFURLRef appUrlRef;
            appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(),CFSTR("/src/fileio/templates/pw.in"),NULL,NULL);
            CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
            const char* pathString = CFStringGetCStringPtr(filePathRef,kCFStringEncodingUTF8);
#else
			const char* pathString = "src/fileio/templates/pw.in";
#endif
            inFile.setFileName(pathString);
#ifdef __APPLE__
            CFRelease(appUrlRef);
            CFRelease(filePathRef);
#endif
			QString filename = QFileDialog::getSaveFileName(NULL, QFileDialog::tr("Save File"), "", QFileDialog::tr("Text files(*.txt;*.in)"));
			outFile.setFileName(filename);
			structure->file = filename;
		}
	}
	if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}
	if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return false;
	}

	QTextStream in(&inFile);
	QTextStream out(&outFile);
	out.setRealNumberPrecision(9);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		if (line.contains("nat"))
		{
			out << "nat=" << QString::number(structure->getAtoms().size())<<endl;
		}
		else if (line.contains("ATOMIC_SPECIES"))
		{
			out << line << endl;
			QString atom_symbol;
			std::vector<Particle>*atoms = &(structure->getAtoms());
			for (uint i = 0; i < atoms->size(); i++)
			{
				QString atom_symbol1 = QString((*atoms)[i].getSymbol().c_str());
				if (atom_symbol!=atom_symbol1)
				{
					out << atom_symbol1 << "  " << (*atoms)[i].getWeight() <<"  "<<"PROVIDE .UPF FILE HERE"<< endl;
					atom_symbol = atom_symbol1;
				}
			}
			out << endl;
			while (!line.isEmpty())
			{
				line = in.readLine();
			}
		}
		else if (line.contains("CELL_PARAMETERS"))
		{
			out << line << endl;
			while (!line.isEmpty())
			{
				line = in.readLine();
			}
			glm::dmat3& mat = structure->getCell();
			out << mat[0][0] << "  " << mat[0][1] << "  " << mat[0][2] << endl
				<< mat[1][0] << "  " << mat[1][1] << "  " << mat[1][2] << endl
				<< mat[2][0] << "  " << mat[2][1] << "  " << mat[2][2] << endl;
			out << line << endl;

		} 
		else if (line.contains("ATOMIC_POSITIONS"))
		{
			out << line << endl;
			while (!line.isEmpty())
			{
				line = in.readLine();
			}
			std::vector<Particle>*atoms = &(structure->getAtoms());
			std::vector<glm::dvec3> coords = structure->getRelativeAtomCoords();
			for (int i =0;i<structure->getAtoms().size();i++)
			{
				double coords1 = coords[i][0];
				out << (*atoms)[i].getSymbol().c_str() << "\t" << coords[i][0] << "  " << coords[i][1] << "  " << coords[i][2] << endl;
			}
			out << line << endl;

		}
		else
			out << line<<endl;
	}
	inFile.close();
	if (!inFile.fileName().contains("pw.in"))
	{

		inFile.remove();
	}
	outFile.close();
	outFile.rename(structure->file);
	return true;
}
