static void
die(const char * msg)
{
  fprintf(stderr, "# fatal error: %s\n", msg);
  exit(2);
}

static void
reportErr(uint32_t status)
{
  woffPrintStatus(stderr, status, "### ");
  exit(status & 0xff);
}

const uint8_t *
readFile(const char * name, uint32_t * len)
{
  FILE * inFile = fopen(name, "rb");
  if (!inFile) {
    char buf[200];
    sprintf(buf, "unable to open file %s", name);
    die(buf);
  }

  if (fseek(inFile, 0, SEEK_END) != 0)
    die("seek failure");
  *len = ftell(inFile);
  if (fseek(inFile, 0, SEEK_SET) != 0)
    die("seek failure");

  uint8_t * data = (uint8_t *) malloc(*len);
  if (!data)
    die("malloc failure");
  if (fread(data, 1, *len, inFile) != *len)
    die("file read failure");
  fclose(inFile);

  return data;
}
