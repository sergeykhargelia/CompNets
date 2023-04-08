import argparse
from ftplib import FTP

def upload(ftp_obj, directory, server_file_name, local_file_path, file_type):
	ftp_obj.cwd(directory)
	
	if file_type == 'text':
		with open(local_file_path) as fobj:
			ftp_obj.storlines('STOR ' + server_file_name, fobj)
	else:
		with open(local_file_path) as fobj:
			ftp_obj.storbinary('STOR ' + server_file_name, fobj, 1024)



def download(ftp_obj, directory, server_file_name, local_file_path):
	ftp_obj.cwd(directory)
	with open(local_file_path, 'wb') as f:
		ftp_obj.retrbinary('RETR ' + server_file_name, f.write)


def list(ftp_obj, dir):
	dirs = []
	files = []

	for item in ftp_obj.mlsd(dir):
		if item[1]['type'] == 'dir':
			dirs.append(item[0])
		else: 
			files.append(item[0])

	print("Directories:")
	print('\n'.join(sorted(dirs)))

	print("\nFiles:")
	print('\n'.join(sorted(files)))


if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	parser.add_argument("-ho", "--host", type=str)
	parser.add_argument('-u', '--username', type=str, default='')
	parser.add_argument('-p', '--password', type=str, default='')
	parser.add_argument('-a', '--action_type', type=str)
	parser.add_argument('-d', '--directory', type=str, default='')
	parser.add_argument('-s', '--server_file_name', type=str, default='')
	parser.add_argument('-l', '--local_file_path', type=str, default='')
	parser.add_argument('-t', '--upload_file_type', type=str, default='text')
	args = parser.parse_args()

	try:
		ftp = FTP(args.host)
		ftp.login(args.username, args.password)
	except:
		print('Failed to connect to the server.')
		exit(1)

	try:
		if args.action_type == 'list':
			list(ftp, args.directory)
		elif args.action_type == 'download':
			download(ftp, args.directory, args.server_file_name, args.local_file_path)
		elif args.action_type == 'upload':
			upload(ftp, args.directory, args.server_file_name, args.local_file_path, args.upload_file_type)
		else:
			print('Unknown action type.')
	except:
		print("Failed to execute action.")

	ftp.quit()