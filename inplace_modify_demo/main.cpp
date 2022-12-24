#include <libCZI.h>
#include <cstdlib>
#include "cmdlineoptions.h"
#include "utilities.h"
#if Inplace_Modify_Demo_UNIX_ENVIRONMENT
#include <clocale>
#endif
#include <iostream>
#include <memory>

using namespace std;
using namespace libCZI;

int main(int argc, char** _argv)
{
    CCmdLineOptions cmd_line_options;
    bool cmd_line_ok;
    try
    {
#if Inplace_Modify_Demo_WIN32_ENVIRONMENT
        CommandlineArgsWindowsHelper args_helper;
        cmd_line_ok = cmd_line_options.Parse(args_helper.GetArgc(), args_helper.GetArgv());
#endif
#if Inplace_Modify_Demo_UNIX_ENVIRONMENT
        setlocale(LC_CTYPE, "");
        cmd_line_ok = cmd_line_options.Parse(argc, argv);
#endif
        if (!cmd_line_ok)
        {
            return EXIT_FAILURE;
        }

        // create the underlying input-output-stream
        const auto io_stream = CreateInputOutputStreamForFile(cmd_line_options.GetCZIFilenameW().c_str());

        // create the reader-writer-object
        const auto reader_writer = CreateCZIReaderWriter();

        // open the CZI-file
        reader_writer->Create(io_stream);

        // read the metadata-segment
        const auto metadata_segment = reader_writer->ReadMetadataSegment();

        // construct the metadata-object from the metadata-segment (use this to query information if required)
        const auto metadata = metadata_segment->CreateMetaFromMetadataSegment();

        // now, create a metadata-builder-object from the XML
        const auto metadata_builder = CreateMetadataBuilderFromXml(metadata->GetXml());

        // modify a node
        const auto comment_node = metadata_builder->GetRootNode()->GetOrCreateChildNode("Metadata/Information/Document/Comment");
        comment_node->SetValue("*** modified by inplace_modify_demo ***");

        // and now, write the modified metadata into the file
        WriteMetadataInfo metadata_info;
        metadata_info.Clear();
        const string source_metadata_xml = metadata_builder->GetXml();
        metadata_info.szMetadata = source_metadata_xml.c_str();
        metadata_info.szMetadataSize = source_metadata_xml.size();
        reader_writer->SyncWriteMetadata(metadata_info);

        // close the file (important!)
        reader_writer->Close();
    }
    catch (exception& exception)
    {
        cerr << "Exception occured: " << exception.what() << ".";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
